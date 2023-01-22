#include "shader.h"
#include <spdlog/spdlog.h>

Shader::Shader(const char *code, Type type)
{
    create(code, type);
}

void Shader::create(const char *code, Type type)
{
    id = glCreateShader(type);
    glShaderSource(id, 1, &code, nullptr);
    glCompileShader(id);

    compileInfo();
}

void Shader::destroy() const
{
    glDeleteShader(id);
}

void Shader::compileInfo()
{
    constexpr int logSize = 512;
    GLint success;
    GLchar infoLog[logSize];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, logSize, NULL, infoLog);
        spdlog::error("ERROR::SHADER::COMPILATION_FAILED\n{}", infoLog);
    }
}
