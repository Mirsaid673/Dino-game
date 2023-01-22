#include "program.h"

#include <fstream>
#include <sstream>

#include <spdlog/spdlog.h>

Program::Program(const Shader &vert, const Shader &frag)
{
    create(vert, frag);
}

Program::Program(const char *vs_file, const char *fs_file)
{
    create(vs_file, fs_file);
}

void Program::create()
{
    id = glCreateProgram();
}

void Program::create(const Shader &vert, const Shader &frag)
{
    create();
    attachShader(vert);
    attachShader(frag);
    link();
}

void Program::create(const char *vs_file, const char *fs_file)
{
    Shader vert(readFile(vs_file).c_str(), Shader::Type::VERTEX);
    Shader frag(readFile(fs_file).c_str(), Shader::Type::FRAGMENT);

    create(vert, frag);

    vert.destroy();
    frag.destroy();
}

void Program::destroy() const
{
    glDeleteProgram(id);
}

void Program::attachShader(const Shader &shader) const
{
    glAttachShader(id, shader.getID());
}

void Program::link() const
{
    glLinkProgram(id);
    linkInfo();
}

void Program::use() const
{
    glUseProgram(id);
}

void Program::unuse() const
{
    glUseProgram(0);
}

void Program::linkInfo() const
{
    constexpr int logSize = 512;
    GLint success;
    GLchar infoLog[logSize];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, logSize, nullptr, infoLog);
        spdlog::error("ERROR::PROGRAM::LINK_FAILED\n{}", infoLog);
    }
}

std::string Program::readFile(const char *file) const
{
    std::string text;
    std::ifstream vShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    try
    {
        vShaderFile.open(file);
        std::stringstream vShaderStream;

        vShaderStream << vShaderFile.rdbuf();

        vShaderFile.close();
        text = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        spdlog::error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    }

    return text;
}

int Program::getUniformLoc(const char *name) const
{
    return glGetUniformLocation(id, name);
}

template <>
void Program::setScalar<int>(const char *name, int v) const
{
    glUniform1i(getUniformLoc(name), v);
}

template <>
void Program::setScalar<uint32_t>(const char *name, uint32_t v) const
{
    glUniform1ui(getUniformLoc(name), v);
}

template <>
void Program::setScalar<float>(const char *name, float v) const
{
    glUniform1f(getUniformLoc(name), v);
}

template <>
void Program::setScalar<double>(const char *name, double v) const
{
    glUniform1d(getUniformLoc(name), v);
}

void Program::setVec2(const char *name, const glm::vec2 &v) const
{
    glUniform2fv(getUniformLoc(name), 1, &v.x);
}

void Program::setVec3(const char *name, const glm::vec3 &v) const
{
    glUniform3fv(getUniformLoc(name), 1, &v.x);
}

void Program::setVec4(const char *name, const glm::vec4 &v) const
{
    glUniform4fv(getUniformLoc(name), 1, &v.x);
}

void Program::setMat2(const char *name, const glm::mat2 &v) const
{
    glUniformMatrix2fv(getUniformLoc(name), 1, GL_FALSE, &v[0][0]);
}

void Program::setMat3(const char *name, const glm::mat3 &v) const
{
    glUniformMatrix3fv(getUniformLoc(name), 1, GL_FALSE, &v[0][0]);
}

void Program::setMat4(const char *name, const glm::mat4 &v) const
{
    glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, &v[0][0]);
}

void Program::vertexAttrib(uint32_t index, const glm::vec2 &v)
{
    glVertexAttrib2fv(index, &v.x);
}

void Program::vertexAttrib(uint32_t index, const glm::vec3 &v)
{
    glVertexAttrib3fv(index, &v.x);
}
void Program::vertexAttrib(uint32_t index, const glm::vec4 &v)
{
    glVertexAttrib4fv(index, &v.x);
}

void Program::vertexAttrib(uint32_t index, int v)
{
    glVertexAttribI1i(index, v);
}
void Program::vertexAttrib(uint32_t index, float v)
{
    glVertexAttrib1f(index, v);
}
void Program::vertexAttrib(uint32_t index, double v)
{
    glVertexAttrib1d(index, v);
}

Program Program::basic;
Program Program::basic2d;
Program Program::colored2d;
Program Program::skybox;
Program Program::framebuffer;

void Program::initPrograms()
{
    basic.create("../Engine/openGL/Program/Shaders/basic.vert",
                 "../Engine/openGL/Program/Shaders/basic.frag");

    basic2d.create("../Engine/openGL/Program/Shaders/2d/basic.vert",
                   "../Engine/openGL/Program/Shaders/2d/basic.frag");

    colored2d.create("../Engine/openGL/Program/Shaders/2d/colored.vert",
                   "../Engine/openGL/Program/Shaders/2d/colored.frag");

    skybox.create("../Engine/openGL/Program/Shaders/skybox.vert",
                  "../Engine/openGL/Program/Shaders/skybox.frag");
    framebuffer.create("../Engine/openGL/Program/Shaders/framebuffer/basic.vert",
                       "../Engine/openGL/Program/Shaders/framebuffer/basic.frag");
}

void Program::destroyPrograms()
{
    basic.destroy();
    basic2d.destroy();
    colored2d.destroy();
    skybox.destroy();
    framebuffer.destroy();
}