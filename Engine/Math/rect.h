#pragma once

#include <glm/glm.hpp>

struct Rect
{
    glm::vec2 origin;
    glm::vec2 size;

    Rect() = default;
    Rect(const glm::vec2& _origin, const glm::vec2& _size) : origin(_origin), size(_size) {}
};