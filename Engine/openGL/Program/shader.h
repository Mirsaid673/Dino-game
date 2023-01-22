#pragma once

#include <GL/glew.h>

class Shader
{
private:
    GLuint id = -1;

public:
    enum Type
    {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

private:
    void compileInfo();

public:
    Shader() = default;
    Shader(const char *code, Type type);

    void create(const char *code, Type type);
    void destroy() const;

    GLuint getID() const { return id; }
};