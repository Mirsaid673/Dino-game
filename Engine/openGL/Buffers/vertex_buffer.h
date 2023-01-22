#pragma once

#include <GL/glew.h>

class VertexBuffer
{
private:
    GLuint id = -1;
    uint32_t size = 0;

public:
    VertexBuffer() = default;
    VertexBuffer(const void *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);

    void create(const void *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);

    void bind() const;
    void unbind() const;
    void destroy() const;

    uint32_t getSize() const { return size; }
};