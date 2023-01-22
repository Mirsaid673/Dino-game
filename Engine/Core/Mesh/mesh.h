#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_st;

    Vertex() = default;
    Vertex(const glm::vec3 &_position,
           const glm::vec3 &_normal,
           const glm::vec2 &_texture_st) : position(_position), normal(_normal), texture_st(_texture_st) {}
};

class Mesh
{
public:
    enum Primitive
    {
        POINTS = GL_POINTS,

        LINES = GL_LINES,
        LINE_STRIP = GL_LINE_STRIP,
        LINE_LOOP = GL_LINE_LOOP,

        TRIANGLES = GL_TRIANGLES,
        TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
        TRIANGLE_FAN = GL_TRIANGLE_FAN,
    };

private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    Primitive mode = Primitive::TRIANGLES;

public:
    Mesh() = default;
    Mesh(const std::vector<Vertex> &v, const std::vector<uint32_t> &i) : vertices(v), indices(i) {}

    void setVertices(const std::vector<Vertex> &v) { vertices = v; }
    void setIndices(const std::vector<uint32_t> &i) { indices = i; }

    const std::vector<Vertex> &getVertices() const { return vertices; }
    const std::vector<uint32_t> &getIndices() const { return indices; }

    void setMode(Primitive p) { mode = p; }
    Primitive getMode() const { return mode; }
};