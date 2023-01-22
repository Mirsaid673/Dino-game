#pragma once

#include "Math/transform2d.h"

class Camera2d
{
private:
    glm::mat3x2 proj;
    float width = 0;
    float height = 0;

public:
    Transform2d transform;

    Camera2d() : proj(1.0f) {}

    void ortho(float left, float right, float top, float bottom);
    void ortho(float width, float height);

    glm::mat3 getView() const;
    glm::mat3x2 getView3x2() const;

    glm::mat3 getProjection() const { return glm::mat3(proj); }
    glm::mat3x2 getProjection3x2() const { return proj; }

    glm::mat3x2 getPV3x2() const;
    glm::mat3 getPV() const { return getProjection() * getView(); }

    float getWidth() const { return width; }
    float getHeight() const { return height; }
    glm::vec2 getSize() const { return {width, height}; }
};