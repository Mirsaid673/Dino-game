#pragma once

#include <glm/glm.hpp>

class Basis
{
private:
    glm::mat3 basis;

public:
    Basis() : basis(1.0f) {}

    void rotate(float angle, const glm::vec3 &axis);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    glm::vec3 &operator[](size_t ind) { return basis[ind]; }
    const glm::vec3 &operator[](size_t ind) const { return basis[ind]; }
    operator glm::mat3 &() { return basis; }
    operator glm::mat4() const { return glm::mat4(basis); }
};