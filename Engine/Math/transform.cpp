#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>

void Transform::translate(const glm::vec3 &v)
{
    origin += b[0] * v[0] + b[1] * v[1] + b[2] * v[2];
}

glm::mat4 Transform::getMatrix() const
{
    glm::mat4 r;
    r[0] = glm::vec4(b[0], 0);
    r[1] = glm::vec4(b[1], 0);
    r[2] = glm::vec4(b[2], 0);
    r[3] = glm::vec4(origin, 1);
    return r;
}         