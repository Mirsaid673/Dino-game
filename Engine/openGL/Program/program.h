#pragma once

#include "shader.h"

#include <string>
#include <glm/glm.hpp>

class Program
{
private:
    GLuint id = -1;

    void linkInfo() const;
    std::string readFile(const char *file) const;

public:
    Program() = default;
    Program(const Shader &vert, const Shader &frag);
    Program(const char *vs_file, const char *fs_file);

    void create();
    void create(const Shader &vert, const Shader &frag);
    void create(const char *vs_file, const char *fs_file);
    void destroy() const;
    void attachShader(const Shader &shader) const;
    void link() const;

    void use() const;
    void unuse() const;

    int getUniformLoc(const char *name) const;

    void setPVM(const glm::mat4 &PVM) const { setMat4("PVM", PVM); }
    void setPVM(const glm::mat3 &PVM) const { setMat3("PVM", PVM); }

    template <typename T>
    void setScalar(const char *name, T v) const;

    void setVec2(const char *name, const glm::vec2 &v) const;
    void setVec3(const char *name, const glm::vec3 &v) const;
    void setVec4(const char *name, const glm::vec4 &v) const;

    void setMat2(const char *name, const glm::mat2 &v) const;
    void setMat3(const char *name, const glm::mat3 &v) const;
    void setMat4(const char *name, const glm::mat4 &v) const;

    void vertexAttrib(uint32_t index, const glm::vec2& v);
    void vertexAttrib(uint32_t index, const glm::vec3& v);
    void vertexAttrib(uint32_t index, const glm::vec4& v);

    void vertexAttrib(uint32_t index, int v);
    void vertexAttrib(uint32_t index, float v);
    void vertexAttrib(uint32_t index, double v);

    static void initPrograms();
    static void destroyPrograms();

    static Program basic;
    static Program basic2d;
    static Program colored2d;
    static Program skybox;
    static Program framebuffer;
};