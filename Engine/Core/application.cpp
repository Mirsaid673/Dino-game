#include "application.h"

Application::Application()
{
    app_init();
}

void Application::app_init()
{
    Window::init();

    window.create(800, 600, "title");
    window.makeCurrent();
    input.init(window);
    Time::init();

    Renderer::init();
    window.debug();

    Renderer::setViewport(window.getSize());
    Renderer::setCamera(camera);
    Renderer::setCamera2d(camera2d);
    GPU::gpu.init();

    Program::initPrograms();

    camera.perspective(glm::radians(90.0f), (float)window.getWidth() / float(window.getHeight()), 0, 100);
    camera2d.ortho(-1, 1, 1, -1);
}

void Application::app_determinate()
{
    Program::destroyPrograms();
    window.destroy();
    Window::cleanup();
}

int Application::run()
{
    init();

    // cursor pos is incorrect in first frames if not do this
    Input::updateInput();
    input.update();

    while (running)
    {
        if (window.shouldClose())
            running = false;

        window.updateSize();
        if (window.resized())
        {
            Renderer::setViewport(window.getSize());
            onResize();
        }
        Renderer::clearBuffers();

        update();
        current_scene->update();
        current_scene->draw();
        draw();

        window.swapBuffers();
        input.update();
        Input::updateInput();
        Time::update();
    }

    current_scene->destroy();
    determinate();
    app_determinate();

    return 0;
}

void Application::set_scene(Scene &scene)
{
    current_scene->destroy();
    current_scene = &scene;
    
    scene.update();
}