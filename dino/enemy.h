#pragma once

#include "physics.h"
#include "../Engine/Core/application.h"
#include "my_shader.h"
#include <glm/gtc/random.hpp>

class Enemy : public Node, public Collider
{
private:
    RID quad;
    Material m;
    Transform2d transform;
    b2Body *body;

public:
    float speed = 5.f;
    Enemy(const glm::vec2 &pos = glm::vec2(4, -3))
    {
        id = Collider::ID::ENEMY;

        glm::vec2 size = {1, 1};

        quad = GPU::gpu.getDeafultQuad();

        transform.origin = pos;
        transform.scale(size);

        b2BodyDef def;
        b2BodyUserData user_data;
        user_data.pointer = (uintptr_t)((Collider *)this);
        def.userData = user_data;
        def.fixedRotation = true;
        def.position.Set(pos.x, pos.y);
        def.type = b2_kinematicBody;

        b2PolygonShape shape;
        shape.SetAsBox(size.x / 4.0f, size.y);

        b2FixtureDef fixture;
        fixture.shape = &shape;

        body = physics.createBody(&def);

        body->CreateFixture(&fixture);
    }

    void init() override
    {
        m.program = &MyShader::program;
        setRandomTexture();
    }

    void setRandomTexture()
    {
        int count = sizeof(textures) / sizeof(textures[0]);
        int random = glm::linearRand(0, 2);

        m.texture = textures[random];
    }

    static float spawnPoint;
    static float destroyPoint;

    void update() override
    {
        b2Vec2 pos = body->GetPosition();
        transform.origin = {pos.x, pos.y};

        transform.origin -= glm::vec2(speed * Time::delta_time, 0);
        if (transform.origin.x <= destroyPoint)
            respawn();

        body->SetTransform({transform.origin.x, transform.origin.y}, 0.0f);
    }

    void respawn()
    {
        transform.origin.x = spawnPoint;
        setRandomTexture();
    }

    void draw() override
    {
        Renderer::setMaterial(m);
        Renderer::setTransform2d(transform.getMatrix());

        Renderer::drawVAO(quad);
    }

    static RID textures[3];

    static void initialize()
    {
        int count = sizeof(textures) / sizeof(textures[0]);

        Image::setFlipOnLoad(true);
        for (int i = 0; i < count; i++)
        {
            textures[i] = GPU::gpu.createTexture(("../dino/resource/enemy" + std::to_string(i + 1) + ".png").c_str());
            GPU::gpu.textureFilter(textures[i], Texture::Filter::NEAREST);
            GPU::gpu.textureWrapMode(textures[i], Texture::WrapMode::MIRRORED_REPEAT);
        }
    }
};

float Enemy::spawnPoint = 10;
float Enemy::destroyPoint = -10;

RID Enemy::textures[3];