#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(const void *data, uint32_t size, GLenum usage)
{
    create(data, size, usage);
}

void VertexBuffer::create(const void *data, uint32_t size, GLenum usage)
{
    this->size = size;
    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ARRAY_BUFFER, size, (GLvoid *)data, usage);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::destroy() const
{
    glDeleteBuffers(1, &id);
}
