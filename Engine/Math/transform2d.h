#pragma once

#include "basis2d.h"

class Transform2d
{
public:
    Basis2d basis;
    glm::vec2 origin;

    Transform2d() : origin(0.0f) {}

    void translate(const glm::vec2 &v);

    void rotate(float angle) { basis.rotate(angle); }
    void setRotation(float angle) { basis.setRotation(angle); }
    float getRotation() const { return basis.geRotation(); }
    void scale(const glm::vec2 &s) { basis.scale(s); }

    glm::mat3 getMatrix() const;
    glm::mat3x2 getMatrix3x2() const;
};