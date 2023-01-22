#include "camera2d.h"

void Camera2d::ortho(float width, float height)
{
    ortho(-width / 2.0f, width / 2.0f, height / 2.0f, -height / 2.0f);
}

void Camera2d::ortho(float left, float right, float top, float bottom)
{
    width = right - left;
    height = top - bottom;
    proj[0][0] = 2.0f / (right - left);
    proj[1][1] = 2.0f / (top - bottom);

    proj[2][0] = -(right + left) / (right - left);
    proj[2][1] = -(top + bottom) / (top - bottom);
}

glm::mat3 Camera2d::getView() const
{
    return glm::inverse(transform.getMatrix());
}

glm::mat3x2 Camera2d::getView3x2() const
{
    glm::mat3x2 r(transform.getMatrix3x2());
    // inversing
    r[2] = -r[2];
    r[0][1] = -r[0][1];
    r[1][0] = -r[1][0];
    return r;
}

glm::mat3x2 Camera2d::getPV3x2() const
{
    return glm::mat3x2(getProjection() * glm::mat3(getView3x2()));
}