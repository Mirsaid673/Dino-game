#include "input.h"

void Input::updateInput()
{
    glfwPollEvents();
}

void Input::init(const Window &_window)
{
    window = _window;
    for (int i = 0; i < sizeof(last_keys_state) / sizeof(last_keys_state[0]); i++)
    {
        last_keys_state[i] = glfwGetKey(window, i);
    }

    for (int i = 0; i < sizeof(last_mouse_butons_state) / sizeof(last_mouse_butons_state[0]); i++)
    {
        last_mouse_butons_state[i] = glfwGetMouseButton(window, i);
    }

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    cursor_pos = glm::ivec2(x, y);
    cursor_last_pos = cursor_pos;

    glfwSetWindowUserPointer(window, (void*)this);
    glfwSetScrollCallback(window, mouseScrollCallback);
    muouse_scroll = 0.0;
}

void Input::update()
{
    for (int i = 0; i < sizeof(last_keys_state) / sizeof(last_keys_state[0]); i++)
    {
        last_keys_state[i] = glfwGetKey(window, i);
    }

    for (int i = 0; i < sizeof(last_mouse_butons_state) / sizeof(last_mouse_butons_state[0]); i++)
    {
        last_mouse_butons_state[i] = glfwGetMouseButton(window, i);
    }

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    cursor_last_pos = cursor_pos;
    cursor_pos = glm::ivec2(x, y);
    muouse_scroll = 0.0;
}

void Input::mouseScrollCallback(GLFWwindow *wnd, double, double y_offset)
{
    Input *self = reinterpret_cast<Input*>(glfwGetWindowUserPointer(wnd));
    self->muouse_scroll = y_offset;
}