#pragma once

#include "../Engine/Core/node.h"
#include "physics.h"

class Ground : public Node, public Collider
{
private:
    RID quad;
    Transform2d transform;
    b2Body *body;
    float speed = 5.0f;

public:
    Ground(const glm::vec2 &pos = glm::vec2(0, -5))
    {
        id = Collider::ID::GROUND;
        glm::vec2 collider_pos = {0, -5};
        glm::vec2 size = {10, 1};

        quad = GPU::gpu.getDeafultQuad();

        transform.scale(size);
        transform.origin = pos + glm::vec2(0, 1.f);

        b2BodyDef def;
        b2BodyUserData data;
        data.pointer = (uintptr_t)((Collider *)this);
        def.userData = data;
        def.position.Set(collider_pos.x, collider_pos.y);

        b2PolygonShape shape;
        shape.SetAsBox(size.x, size.y);

        body = physics.createBody(&def);
        body->CreateFixture(&shape, 0);
    }
    void init() override
    {
    }

    static float spawnPoint;
    static float destroyPoint;

    void update() override
    {
        transform.origin -= glm::vec2(speed * Time::delta_time, 0);
        if (transform.origin.x <= destroyPoint)
            transform.origin.x = transform.origin.x - destroyPoint + spawnPoint;
    }

    void draw() override
    {
        Renderer::setMaterial(m);
        Renderer::setTransform2d(transform.getMatrix());

        Renderer::drawVAO(quad);
    }

    static Material m;

    static void initialize()
    {
        Image::setFlipOnLoad(true);
        m.program = &Program::basic2d;
        m.texture = GPU::gpu.createTexture("../dino/resource/ground.jpg");
        GPU::gpu.textureFilter(m.texture, Texture::Filter::NEAREST);
    }
};

float Ground::spawnPoint =  20;
float Ground::destroyPoint = -20;
Material Ground::m;