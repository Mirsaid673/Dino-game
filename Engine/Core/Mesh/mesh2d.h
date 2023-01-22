#pragma once

#include "mesh.h"

struct Vertex2d
{
    glm::vec2 position;
    glm::vec2 texture_st;

    Vertex2d() = default;
    Vertex2d(const glm::vec2 &_position) : position(_position) {}
    Vertex2d(const glm::vec2 &_position,
             const glm::vec2 &_texture_st) : position(_position), texture_st(_texture_st) {}
};

class Mesh2d
{
private:
    std::vector<Vertex2d> vertices;
    std::vector<uint32_t> indices;
    Mesh::Primitive mode = Mesh::Primitive::TRIANGLES;

public:
    Mesh2d() = default;
    Mesh2d(const std::vector<Vertex2d> &v, const std::vector<uint32_t> &i) : vertices(v), indices(i) {}

    void setVertices(const std::vector<Vertex2d> &v) { vertices = v; }
    void setIndices(const std::vector<uint32_t> &i) { indices = i; }

    const std::vector<Vertex2d> &getVertices() const { return vertices; }
    const std::vector<uint32_t> &getIndices() const { return indices; }

    void setMode(Mesh::Primitive p) { mode = p; }
    Mesh::Primitive getMode() const { return mode; }
};