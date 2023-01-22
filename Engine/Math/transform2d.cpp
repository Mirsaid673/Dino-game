#include "transform2d.h"

void Transform2d::translate(const glm::vec2 &v)
{
    origin += basis[0] * v.x + basis[1] * v.y;
}

glm::mat3x2 Transform2d::getMatrix3x2() const
{
    glm::mat3x2 res(static_cast<glm::mat2>(basis));
    res[2] = origin;
    return res;
}
glm::mat3 Transform2d::getMatrix() const
{
    glm::mat3 res(static_cast<glm::mat2>(basis));
    res[2] = glm::vec3(origin, 1);
    return res;
}