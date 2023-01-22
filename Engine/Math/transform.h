#pragma once

#include "basis.h"

class Transform
{
public:
    Basis b;
    glm::vec3 origin;

    Transform() : origin(0.0f) {}

    void translate(const glm::vec3 &v);

    void rotate(float angle, const glm::vec3 &axis) { b.rotate(angle, axis); }
    void rotateX(float angle) { b.rotateX(angle); }
    void rotateY(float angle) { b.rotateY(angle); }
    void rotateZ(float angle) { b.rotateZ(angle); }

    glm::mat4 getMatrix() const;

    glm::mat4 operator*(const glm::mat4 &m) { return getMatrix() * m; }
    glm::mat4 operator*(const Transform &t) { return getMatrix() * t.getMatrix(); }
};