#include "basis2d.h"

void Basis2d::rotate(float angle)
{
    Basis2d b;
    b.setRotation(angle);
    basis *= static_cast<glm::mat2>(b);
}

void Basis2d::setRotation(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);
    basis[0][0] = basis[1][1] = c;
    basis[0][1] = s;
    basis[1][0] = -s;
}

float Basis2d::geRotation() const
{
    return std::atan2(basis[0].x, basis[0].y);
}

void Basis2d::scale(const glm::vec2 &s)
{
    basis[0] *= s.x;
    basis[1] *= s.y;
}