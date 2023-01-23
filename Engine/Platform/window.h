#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
private:
    static void resize_callback(GLFWwindow *window, int width, int height);

    GLFWwindow *m_window;
    glm::ivec2 last_size;
    glm::ivec2 size;
    glm::ivec2 min_size = glm::ivec2(-1);
    glm::ivec2 max_size = glm::ivec2(-1);

    const char *m_title;

public:
    Window() = default;
    Window(uint32_t width, uint32_t height, const char *title);

    void create(uint32_t width, uint32_t height, const char *title);
    void destroy();
    void makeCurrent();

    bool shouldClose();
    void swapBuffers();
    void updateSize();

    operator GLFWwindow *() const { return m_window; }
    GLFWwindow *getWindowPtr() const { return m_window; }

    void setMinSize(const glm::ivec2 &size)
    {
        min_size = size;
        glfwSetWindowSizeLimits(m_window, min_size.x, min_size.y, max_size.x, max_size.y);
    }
    void setMaxSize(const glm::ivec2 &size)
    {
        max_size = size;
        glfwSetWindowSizeLimits(m_window, min_size.x, min_size.y, max_size.x, max_size.y);
    }
    void setSizeLimits(const glm::ivec2 &minimum_size, const glm::ivec2 &maximum_size)
    {
        min_size = minimum_size;
        max_size = maximum_size;
        glfwSetWindowSizeLimits(m_window, min_size.x, min_size.y, max_size.x, max_size.y);
    }
    const glm::ivec2 &getSize() const { return size; }
    int getWidth() const { return size.x; }
    int getHeight() const { return size.y; }
    const char *getTitle() const { return m_title; }

    bool resized() const { return last_size != size; }

    static void init();
    static void cleanup();
    static void debug();
};