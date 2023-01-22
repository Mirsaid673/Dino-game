#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private:
    GLuint id = -1;
    uint32_t size = 0;

    uint32_t count = 0;
    GLenum data_type;

public:
    IndexBuffer() = default;

    IndexBuffer(const uint32_t *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);
    IndexBuffer(const uint16_t *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);

    void create(const uint32_t *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);
    void create(const uint16_t *data, uint32_t size, GLenum usage = GL_STATIC_DRAW);

    void bind() const;
    void unbind() const;
    void destroy() const;

    GLenum getDataType() const { return data_type; }
    uint32_t getCount() const { return count; }

    uint32_t getSize() const { return size; }
};