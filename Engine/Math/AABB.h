#pragma once

#include <glm/glm.hpp>

class AABB
{
public:
    glm::vec2 left_bottom;
    glm::vec2 right_top;
    AABB() = default;
    AABB(const glm::vec2 &l_b, const glm::vec2 &r_t) : left_bottom(l_b), right_top(r_t) {}

    bool isPointInside(glm::vec2 p)
    {
        return (p.x < right_top.x) && (p.x > left_bottom.x) && (p.y > left_bottom.y) && (p.y < right_top.y);
    }
};