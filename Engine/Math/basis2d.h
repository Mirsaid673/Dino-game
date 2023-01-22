#pragma once

#include <glm/glm.hpp>

class Basis2d
{
private:
    glm::mat2 basis;

public:
    Basis2d() : basis(glm::mat2(1.0f)) {}

    void rotate(float angle);
    void setRotation(float angle);

    float geRotation() const;

    void scale(const glm::vec2& s);

    glm::vec2 &operator[](unsigned int ind) { return basis[ind]; }
    operator const glm::mat2 &() const { return basis; }
};