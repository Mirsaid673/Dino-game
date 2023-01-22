#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"

#include "vertex_attribs.h"

class VertexArray
{
private:
    GLuint id = -1;
    uint32_t m_index_count = 0;
    uint32_t m_vertex_count = 0;
    GLenum m_index_data_type;
    GLenum m_mode = GL_TRIANGLES;

public:
    VertexArray() = default;

    template <template <class...> class container>
    VertexArray(const VertexBuffer &buffer, container<VertexAttribs> attribs, bool AOS = true);

    void create();
    void destroy() const;

    void bind() const;
    void unbind() const;

    template <template <class...> class container>
    void linkAttribs(const VertexBuffer &buffer, container<VertexAttribs> attribs, bool AOS = true);
    void linkIndexBuffer(const IndexBuffer &ibo);

    void setMode(GLenum mode) { m_mode = mode; }

    uint32_t getIndexCount() const { return m_index_count; }
    uint32_t getVertexCount() const { return m_vertex_count; }
    GLenum getIndexDataType() const { return m_index_data_type; }
    GLenum getMode() const { return m_mode; }
};

template <template <class...> class container>
VertexArray::VertexArray(const VertexBuffer &buffer, container<VertexAttribs> attribs, bool AOS)
{
    create();
    linkAttribs(buffer, attribs, AOS);
}

template <template <class...> class container>
void VertexArray::linkAttribs(const VertexBuffer &buffer, container<VertexAttribs> attribs, bool AOS)
{
    uint32_t vertex_size_in_bytes = 0;
    for (const auto &attrib : attribs)
        vertex_size_in_bytes += attrib.getCount() * 4;

    m_vertex_count = buffer.getSize() / vertex_size_in_bytes;

    bind();

    GLuint stride = 0;
    GLuint offset = 0;

    if (AOS)
        for (const auto &attrib : attribs)
            stride += attrib.getSize();
    else
        stride = 0;

    buffer.bind();
    for (const auto &attrib : attribs)
    {
        glEnableVertexAttribArray(attrib.getIndex());
        glVertexAttribPointer(attrib.getIndex(), attrib.getCount(), attrib.getType(), false, stride, reinterpret_cast<GLvoid *>(offset));

        if (AOS)
            offset += attrib.getSize();
        else
            offset += m_vertex_count * attrib.getSize();
    }

    unbind();
}