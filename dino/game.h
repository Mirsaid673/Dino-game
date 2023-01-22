#pragma once

#include "../Engine/Core/application.h"
#include "dino.h"
#include "ground.h"
#include "physics.h"
#include "enemy.h"

class Game : public Application
{
    Ground ground;
    Dino dino;
    Enemy enemy;
    void init() override
    {
        camera2d.ortho((float)window.getWidth() / (float)window.getHeight() * scale, scale);
        Renderer::setClearColor(glm::vec3(1));
        scene.addNode(physics);
        scene.addNode(ground);
        scene.addNode(dino);
        scene.addNode(enemy);
    }

    float scale = 10.0f;
    void onResize() override
    {
        camera2d.ortho((float)window.getWidth() / (float)window.getHeight() * scale, scale);
    }

    void update() override
    {
        if (input.getKeyDown(GLFW_KEY_ESCAPE) || dino.game_over)
            running = false;
    }
};