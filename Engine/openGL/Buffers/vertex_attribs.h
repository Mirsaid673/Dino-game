#pragma once

#include <GL/glew.h>

#include <vector>

struct VertexAttribs
{
private:
    static const GLuint count[];

public:
    static std::vector<VertexAttribs> POS_NORM_TEX;
    static std::vector<VertexAttribs> POS2D_TEX;

    enum Type
    {
        POSITION    = 0, // vec3
        NORMAL      = 1, // vec3
        COLOR       = 2, // vec3
        TEXTURE_ST  = 3, // vec2
        TEXTURE_ST2 = 4, // vec2

        POSITION2D  = 5, // vec2
        COLOR4      = 6, // vec4
    };

    Type type;

    GLuint getIndex() const
    {
        return (GLuint)type;
    }

    GLuint getCount() const
    {
        return count[type];
    }

    GLenum getType() const
    {
        return GL_FLOAT;
    }

    GLuint getSize() const
    {
        return getCount() * sizeof(float);
    }

    VertexAttribs() = default;
    VertexAttribs(Type t) {type = t;}
};