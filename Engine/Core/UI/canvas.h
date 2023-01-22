#pragma once

#include "button.h"
#include "Core/node.h"

class Canvas : public Node
{
private:
    std::vector<Button *> buttons;
    glm::mat3 projection;
    glm::ivec2 size;

public:
    Canvas() : projection(1.0f) {}

    void addButton(Button &b)
    {
        buttons.push_back(&b);
        b.onCanvasResize(size);
    }

    void checkInput();
    void resize(const glm::ivec2 &new_size);

    void update() override;
    void draw() override;
    glm::vec2 getSizeFromPercents(const glm::vec2 &size_in_percents)
    {
        return size_in_percents * glm::vec2(size) / 100.0f;
    }
};