#pragma once

#include "Buffers/vertex_array.h"
#include "Texture/texture.h"
#include "Texture/cubemap.h"
#include "Core/rid.h"
#include "Mesh/mesh.h"
#include "Mesh/mesh2d.h"
#include <vector>

class GPU
{
private:
    std::vector<VertexArray> vertex_arrays;
    std::vector<VertexBuffer> vertex_buffers;
    std::vector<IndexBuffer> index_buffers;
    std::vector<Texture> textures;
    std::vector<CubeMap> cube_maps;

    RID default_cube;
    RID default_quad;
    RID default_button_quad;

public:
    void init();

    //* buffers
    RID createVertexArray();
    RID createVertexArray(RID buffer, std::vector<VertexAttribs> attribs, bool AOS = true);
    void linkAttribs(RID vertex_array, RID vertex_buffer, std::vector<VertexAttribs> attribs, bool AOS = true);
    void linkIndexBuffer(RID vertex_array, RID index_buffer);
    void setMode(RID vertex_array, Mesh::Primitive mode);

    RID createVertexBuffer(const void *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);

    RID createIndexBuffer(const uint32_t *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);
    RID createIndexBuffer(const uint16_t *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);

    VertexArray &getVertexArray(RID id) { return vertex_arrays[id]; }
    VertexBuffer &getVertexBuffer(RID id) { return vertex_buffers[id]; }
    IndexBuffer &getIndexBuffer(RID id) { return index_buffers[id]; }
    //* meshes
    RID loadMesh(const Mesh &mesh);
    RID loadMesh(const Mesh2d &mesh);

    RID getDeafultCube() const { return default_cube; }
    RID getDeafultQuad() const { return default_quad; }
    RID getDeafultButtonQuad() const { return default_button_quad; }

    //* textures
    RID createTexture(const Image &image, uint32_t mipmap_levels = 0, Texture::InternalFormat in_f = Texture::InternalFormat::NOTHING);
    RID createTexture(const char *file, uint32_t mipmap_levels = 0, Texture::InternalFormat in_f = Texture::InternalFormat::NOTHING);
    Texture &getTexture(RID id) { return textures[id]; }

    void textureFilter(RID id, Texture::Filter filter) { textures[id].filter(filter); }
    void textureWrapMode(RID id, Texture::WrapMode wrap) { textures[id].wrapMode(wrap); }
    void textureMipmaps(RID id) { textures[id].mipmaps(); }

    //* cube maps

    RID createCubeMap(const std::array<Image, 6> &images, uint32_t mipmap_levels, bool gamma_correcred = false);
    RID createCubeMap(const std::array<const char *, 6> &files, uint32_t mipmap_levels, bool gamma_correcred = false);

    CubeMap &getCubeMap(RID id) { return cube_maps[id]; }
    void cubeMapFilter(RID id, Texture::Filter filter) { cube_maps[id].filter(filter); }
    void cubeMapWrapMode(RID id, Texture::WrapMode wrap) { cube_maps[id].wrapMode(wrap); }
    void cubeMapMipmaps(RID id) { cube_maps[id].mipmaps(); }

    GPU();
    ~GPU();

    static GPU gpu;
};