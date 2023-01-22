#pragma once

#include "Core/Mesh/material.h"
#include "Program/program.h"
#include "gpu.h"
#include <glm/glm.hpp>

class Button
{
public:
    friend class Canvas;

    RID quad = GPU::gpu.getDeafultButtonQuad();
    Material material;
    glm::vec2 origin = glm::vec2(0);
    glm::vec2 size = glm::vec2(0);
    bool enabled = true;

private:
    bool pressed = false;

protected:
    virtual void onMouseDown() {}
    virtual void onMouseUp() {}
    virtual void onMousePress() {}
    virtual void onMouseRelease() {}
    virtual void onCanvasResize(const glm::ivec2 &canvas_size) {}

public:
    glm::mat3 getMatrix()
    {
        glm::mat3 r(0);
        r[0][0] = size.x;
        r[1][1] = size.y;
        r[2] = glm::vec3(origin, 1);
        return r;
    }

    void setPositionByCenter(const glm::vec2 &pos)
    {
        origin = pos - size / 2.0f;
    }

    Button() : material(Program::basic2d) {}
    Button(const glm::vec2 &sz) : material(Program::basic2d), size(sz) {}
    Button(const glm::vec2 &sz, const glm::vec2 &pos) : material(Program::basic2d), size(sz), origin(pos) {}

    void setQuad(RID qd) { quad = qd; }
};