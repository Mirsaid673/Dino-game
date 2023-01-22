#include "basis.h"

#include <glm/gtc/matrix_transform.hpp>

void Basis::rotate(float angle, const glm::vec3& axis)
{
    basis = glm::mat3(glm::rotate(glm::mat4(basis), angle, axis));
}

void Basis::rotateX(float angle)
{
    glm::mat3 r = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1, 0, 0)));
    basis = r * basis;
}

void Basis::rotateY(float angle)
{
    glm::mat3 r = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)));
    basis = r * basis;
}

void Basis::rotateZ(float angle)
{
    glm::mat3 r = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)));
    basis = r * basis;
}