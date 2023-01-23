#pragma once

#include "../Engine/Core/application.h"
#include "dino.h"
#include "ground.h"
#include "physics.h"
#include "enemy.h"
#include "my_shader.h"
#include "bg.h"

class Game : public Application
{
    float offset = 10;
    Background background;
    Dino dino;
    Ground ground1 = Ground({-10, -5});
    Ground ground2 = Ground({10, -5});
    Enemy enemy1 = Enemy({4 + offset * 0, -3});
    Enemy enemy2 = Enemy({4  + offset * 1, -3});

    void init() override
    {
        MyShader::initialize();
        Ground::initialize();
        Enemy::initialize();
        camera2d.ortho((float)window.getWidth() / (float)window.getHeight() * scale, scale);
        Renderer::setClearColor(glm::vec3(1));
        scene.addNode(physics);
        scene.addNode(background);
        scene.addNode(ground1);
        scene.addNode(ground2);
        scene.addNode(dino);
        scene.addNode(enemy1);
        scene.addNode(enemy2);
    }

    void determinate() override
    {
        MyShader::determionate();
    }

    float scale = 10.0f;
    float max_aspect = 1.9f;
    void onResize() override
    {
        float height = (float)window.getHeight();
        float width = (float)window.getWidth();
        window.setMaxSize({height * max_aspect+10, height+10});
        camera2d.ortho(width / height * scale, scale);
    }

    void update() override
    {
        if (input.getKeyDown(GLFW_KEY_ESCAPE) || dino.game_over)
            running = false; 
    }
};