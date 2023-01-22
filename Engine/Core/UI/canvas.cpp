#include "canvas.h"

#include "Camera/camera2d.h"
#include "Renderer/renderer.h"
#include "global.h"

bool isPointInside(const glm::ivec2 &p, const Button &b)
{
    return (p.x >= b.origin.x && p.x <= (b.size.x + b.origin.x)) &&
           (p.y >= b.origin.y && p.y <= (b.size.y + b.origin.y));
}

void Canvas::update()
{
    glm::ivec2 cursor = input.getCursorPos();
    for (const auto button : buttons)
    {
        if (not button->enabled)
            continue;

        if (button->pressed)
            button->onMouseDown();
        else
            button->onMouseUp();

        if (isPointInside(input.getCursorPos(), *button))
        {
            if (input.getMouseButtonPress(GLFW_MOUSE_BUTTON_LEFT))
            {
                button->pressed = true;
                button->onMousePress();
            }
            else if (input.getMouseButtonRelease(GLFW_MOUSE_BUTTON_LEFT) && button->pressed)
            {
                button->pressed = false;
                button->onMouseRelease();
            }
        }
        else
        {
            if (button->pressed)
            {
                button->pressed = false;
                button->onMouseRelease();
            }
        }
    }
}

void Canvas::draw()
{
    for (const auto button : buttons)
    {
        if (not button->enabled)
            continue;
        Renderer::setMaterial(button->material);
        button->material.program->use();
        button->material.program->setPVM(projection * button->getMatrix());
        Renderer::drawVAO(button->quad);
    }
}

void Canvas::resize(const glm::ivec2 &new_size)
{
    size = new_size;
    projection[0][0] = 2.0f / (new_size.x);
    projection[1][1] = -2.0f / (new_size.y);

    projection[2][0] = -1.0f;
    projection[2][1] = 1.0f;

    for(auto button : buttons)
    {
        button->onCanvasResize(size);
    }
}