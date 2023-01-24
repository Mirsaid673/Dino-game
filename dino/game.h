#pragma once

#include "../Engine/Core/application.h"
#include "dino.h"
#include "ground.h"
#include "physics.h"
#include "enemy.h"
#include "my_shader.h"
#include "bg.h"
#include <fstream>

class Game : public Application
{
    float offset = 10;
    Background background;
    Dino dino;
    Ground ground1 = Ground({-10, -5});
    Ground ground2 = Ground({10, -5});
    Enemy enemy1 = Enemy({4 + offset * 0, -3});
    Enemy enemy2 = Enemy({4 + offset * 1, -3});
    int best = 0;

    void init() override
    {
        loadBest();
        TextRenderer::loadFont("../dino/resource/ProggyClean.ttf", 48);
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

    void draw()
    {
        TextRenderer::drawText(std::to_string((int)dino.score), {0, 60}, glm::vec3(0.3), 2);
        TextRenderer::drawText("best: " + std::to_string(best), {0, 100}, glm::vec3(0.0), 1);
    }

    void determinate() override
    {
        MyShader::determionate();
    }

    void loadBest()
    {
        std::ifstream input_f("best.txt");
        if (!input_f.is_open())
            spdlog::error("could not open file: best.txt");
        input_f >> best;
    }

    void saveBest(int score)
    {
        std::ofstream output_f("best.txt");
        if (!output_f.is_open())
            spdlog::error("could not create file: best.txt");
        output_f << score;
    }

    float scale = 10.0f;
    float max_aspect = 1.9f;
    void onResize() override
    {
        float height = (float)window.getHeight();
        float width = (float)window.getWidth();
        window.setMaxSize({height * max_aspect + 10, height + 10});
        camera2d.ortho(width / height * scale, scale);
    }

    void update() override
    {
        if (input.getKeyDown(GLFW_KEY_ESCAPE) || dino.game_over)
        {
            if((int)dino.score > best)
                best = (int)dino.score;
            saveBest(best);
            running = false;
        }
        enemy1.speed += Time::delta_time * 0.1;
        enemy2.speed += Time::delta_time * 0.1;
        ground1.speed += Time::delta_time * 0.1;
        ground2.speed += Time::delta_time * 0.1;
    }
};