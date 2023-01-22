#include "index_buffer.h"


IndexBuffer::IndexBuffer(const uint32_t *data, uint32_t size, GLenum usage)
{
    create(data, size, usage);
}

IndexBuffer::IndexBuffer(const uint16_t *data, uint32_t size, GLenum usage)
{
    create(data, size, usage);
}

void IndexBuffer::create(const uint32_t *data, uint32_t size, GLenum usage)
{
    this->size = size;
    data_type = GL_UNSIGNED_INT;
    count = size / sizeof(uint32_t);
    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (GLvoid *)data, usage);
}

void IndexBuffer::create(const uint16_t *data, uint32_t size, GLenum usage)
{
    this->size = size;
    data_type = GL_UNSIGNED_SHORT;
    count = size / sizeof(uint16_t);
    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (GLvoid *)data, usage);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::destroy() const
{
    glDeleteBuffers(1, &id);
}
