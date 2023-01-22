#pragma once

#include "physics.h"
#include "../Engine/Core/application.h"

class Enemy : public Node, public Collider
{
private:
    RID quad;
    Material m;
    Transform2d transform;
    b2Body *body;
    float speed = 5.f;

public:
    Enemy()
    {
        id = Collider::ID::ENEMY;
     
        glm::vec2 pos = {4, -3};
        glm::vec2 size = {1, 1};

        m.program = &Program::basic2d;
        Image::setFlipOnLoad(true);
        m.texture = GPU::gpu.createTexture("../dino/resource/enemy.jpg");
        GPU::gpu.textureFilter(m.texture, Texture::Filter::NEAREST);
        GPU::gpu.textureWrapMode(m.texture, Texture::WrapMode::MIRRORED_REPEAT);
        quad = GPU::gpu.getDeafultQuad();

        transform.origin = pos;
        transform.scale(size);

        b2BodyDef def;
        b2BodyUserData user_data;
        user_data.pointer = (uintptr_t)((Collider *)this);
        def.userData = user_data;
        def.fixedRotation = true;
        def.position.Set(pos.x, pos.y);
        def.type = b2_dynamicBody;

        b2PolygonShape shape;
        shape.SetAsBox(size.x, size.y);

        b2FixtureDef fixture;
        fixture.shape = &shape;

        body = physics.createBody(&def);

        body->CreateFixture(&fixture);
    }

    void update() override
    {
        b2Vec2 pos = body->GetPosition();
        transform.origin = {pos.x, pos.y};

        transform.origin -= glm::vec2(speed * Time::delta_time, 0);
        if(transform.origin.x <= -5.0f)
            transform.origin.x = 5.0;

        body->SetTransform({transform.origin.x, transform.origin.y}, 0.0f);
    }

    void onColliderEnter(b2Fixture *other, b2Contact *cnt) override
    {
    }
    void draw() override
    {
        Renderer::setMaterial(m);
        Renderer::setTransform2d(transform.getMatrix());

        Renderer::drawVAO(quad);
    }
};