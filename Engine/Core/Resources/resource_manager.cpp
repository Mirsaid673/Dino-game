#include "resource_manager.h"

#include "glTF/gltf.hpp"
#include <spdlog/spdlog.h>

size_t getComponontTypeSize(gltf::Accessor::ComponentType ct);
size_t getTypeCount(gltf::Accessor::Type type);
std::vector<Mesh> ResourceManager::loadMesh(const char *file)
{
    const auto gltfFile = gltf::load(file);
    if (!gltfFile)
    {
        spdlog::error("failed to load mesh: {}\n", file);
        return {};
    }
    const auto &gltf = *gltfFile;

    std::vector<Mesh> result_meshes;

    for (int i = 0; i < gltf.nodes.size(); i++)
    {
        if (!gltf.nodes[i].mesh)
            continue;

        size_t mesh_index = *gltf.nodes[i].mesh;
        const gltf::Mesh &mesh = gltf.meshes[mesh_index];
        for (int j = 0; j < mesh.primitives.size(); j++)
        {
            std::vector<uint32_t> indices;

            std::vector<glm::vec3> positions;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec2> texture_coords;

            const gltf::Mesh::Primitive &primitive = mesh.primitives[j];

            // loading vertices
            for (int k = 0; k < primitive.attributes.size(); k++)
            {
                const gltf::Mesh::Primitive::Attribute &attribute = primitive.attributes[k];

                size_t accessor_index = attribute.accessor;
                const gltf::Accessor &accessor = gltf.accessors[accessor_index];

                if (!accessor.bufferView)
                {
                    spdlog::error("accessor ({0}) does not contain buffer view id in file: {0}\n", accessor_index, file);
                    continue;
                }
                size_t buffer_view_index = *accessor.bufferView;
                const gltf::BufferView &buffer_view = gltf.bufferViews[buffer_view_index];
                size_t buffer_index = buffer_view.buffer;
                size_t buffer_offset = buffer_view.byteOffset;

                size_t buffer_stride;
                if (buffer_view.byteStride)
                    buffer_stride = *buffer_view.byteStride;
                else
                    buffer_stride = getComponontTypeSize(accessor.componentType) * getTypeCount(accessor.type);

                const gltf::Buffer &buffer = gltf.buffers[buffer_index];
                const std::vector<uint8_t> &buffer_data = buffer.data;

                if (attribute.id == "POSITION")
                {
                    positions.resize(accessor.count);
                    int data_index = buffer_offset + accessor.byteOffset;
                    for (int m = 0; m < accessor.count; m++)
                    {
                        positions[m] = *reinterpret_cast<const glm::vec3 *>(&buffer_data[data_index]);

                        data_index += buffer_stride;
                    }
                }
                else if (attribute.id == "NORMAL")
                {
                    normals.resize(accessor.count);
                    int data_index = buffer_offset + accessor.byteOffset;
                    for (int m = 0; m < accessor.count; m++)
                    {
                        normals[m] = *reinterpret_cast<const glm::vec3 *>(&buffer_data[data_index]);

                        data_index += buffer_stride;
                    }
                }
                else if (attribute.id == "TEXCOORD_0")
                {
                    texture_coords.resize(accessor.count);
                    int data_index = buffer_offset + accessor.byteOffset;
                    for (int m = 0; m < accessor.count; m++)
                    {
                        texture_coords[m] = *reinterpret_cast<const glm::vec2 *>(&buffer_data[data_index]);

                        data_index += buffer_stride;
                    }
                }
                else
                    continue;
            }

            // loading indices

            size_t indices_accessor_index;
            if (primitive.indices)
                indices_accessor_index = *primitive.indices;
            else
                spdlog::error("mash does not contain indices in file: {0}\n", file);

            const gltf::Accessor &accessor = gltf.accessors[indices_accessor_index];
            size_t buffer_view_index = *accessor.bufferView;

            const gltf::BufferView &buffer_view = gltf.bufferViews[buffer_view_index];
            size_t buffer_offset = buffer_view.byteOffset;
            size_t buffer_stride;
            if (buffer_view.byteStride)
                buffer_stride = *buffer_view.byteStride;
            else
                buffer_stride = getComponontTypeSize(accessor.componentType);

            size_t buffer_index = buffer_view.buffer;
            const gltf::Buffer &buffer = gltf.buffers[buffer_index];
            const std::vector<uint8_t> &buffer_data = buffer.data;

            indices.resize(accessor.count);
            size_t data_index = buffer_offset + accessor.byteOffset;
            for (int k = 0; k < accessor.count; k++)
            {
                indices[k] = *reinterpret_cast<const uint32_t *>(&buffer_data[data_index]);
                data_index += buffer_stride;
            }

            std::vector<Vertex> vertices(positions.size());

            for (int k = 0; k < vertices.size(); k++)
            {
                vertices[k].position = positions[k];
                vertices[k].normal = normals[k];
                vertices[k].texture_st = glm::vec2(texture_coords[k].x, texture_coords[k].y);
            }

            result_meshes.emplace_back(vertices, indices);
        }
    }

    return result_meshes;
}

size_t getComponontTypeSize(gltf::Accessor::ComponentType ct)
{
    switch (ct)
    {
    case gltf::Accessor::ComponentType::Byte:
        return 1;

    case gltf::Accessor::ComponentType::UnsignedByte:
        return 1;

    case gltf::Accessor::ComponentType::Short:
        return 2;

    case gltf::Accessor::ComponentType::UnsignedShort:
        return 2;

    case gltf::Accessor::ComponentType::UnsignedInt:
        return 4;

    case gltf::Accessor::ComponentType::Float:
        return 4;

    default:
        return 0;
    }
}

size_t getTypeCount(gltf::Accessor::Type type)
{
    size_t t = (size_t)type;
    if (t < 10)
        return t;
    else
    {
        int last_num = (t % 10);
        return last_num * last_num;
    }
}

Mesh ResourceManager::createCubeMesh(float x, float y, float z)
{
    std::vector<Vertex> vertices =
        {
            Vertex(glm::vec3(-x, -y, z), glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)),
            Vertex(glm::vec3(x, -y, z), glm::vec3(1.0, -1.0, 1.0), glm::vec2(0, 1)),
            Vertex(glm::vec3(-x, y, z), glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 0)),
            Vertex(glm::vec3(x, y, z), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)),
            Vertex(glm::vec3(-x, -y, -z), glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)),
            Vertex(glm::vec3(x, -y, -z), glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)),
            Vertex(glm::vec3(-x, y, -z), glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)),
            Vertex(glm::vec3(x, y, -z), glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 1)),
        };
    std::vector<uint32_t> indices =
        {0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1};

    Mesh m(vertices, indices);
    m.setMode(Mesh::Primitive::TRIANGLE_STRIP);
    return m;
}

Mesh2d ResourceManager::createQuadMesh(float x, float y)
{
    std::vector<Vertex2d> vertices =
        {
            Vertex2d(glm::vec2(-x, -y), glm::vec2(0, 0)),
            Vertex2d(glm::vec2(-x, y), glm::vec2(0, 1)),
            Vertex2d(glm::vec2(x, -y), glm::vec2(1, 0)),
            Vertex2d(glm::vec2(x, y), glm::vec2(1, 1)),
        };

    std::vector<uint32_t> indices =
        {0, 1, 2, 2, 1, 3};

    return Mesh2d(vertices, indices);
}

Mesh2d ResourceManager::createQuadMesh(const glm::vec2 &left_bottom, const glm::vec2 &right_top)
{
    std::vector<Vertex2d> vertices =
        {
            Vertex2d(left_bottom, glm::vec2(0, 0)),
            Vertex2d(glm::vec2(left_bottom.x, right_top.y), glm::vec2(0, 1)),
            Vertex2d(glm::vec2(right_top.x, left_bottom.y), glm::vec2(1, 0)),
            Vertex2d(right_top, glm::vec2(1, 1)),
        };

    std::vector<uint32_t> indices =
        {0, 1, 2, 2, 1, 3};

    return Mesh2d(vertices, indices);
}