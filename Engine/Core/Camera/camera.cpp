#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::perspective(float angle, float aspect, float near, float far)
{
    proj = glm::perspectiveLH_NO(angle, aspect, near, far);
    proj[3][3] = 1;
}