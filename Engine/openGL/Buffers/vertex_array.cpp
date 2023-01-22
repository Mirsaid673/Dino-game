#include "vertex_array.h"

void VertexArray::create()
{
    glGenVertexArrays(1, &id);
}

void VertexArray::destroy() const
{
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const
{
    glBindVertexArray(id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::linkIndexBuffer(const IndexBuffer &ibo)
{
    m_index_count = ibo.getCount();
    m_index_data_type = ibo.getDataType();

    bind();
    ibo.bind();
    unbind();
}