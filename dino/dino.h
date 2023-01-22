#pragma once

#include "../Engine/Core/application.h"
#include "physics.h"

class Dino : public Node, public Collider
{
private:
    RID quad;
    Material m;
    Transform2d transform;
    b2Body *body;

public:
    bool game_over = false;
    bool grounded = true;

    Dino()
    {
        id = Collider::ID::DINO;
        glm::vec2 pos = {-4, -3};
        glm::vec2 size = {1, 1};

        m.program = &Program::basic2d;
        Image::setFlipOnLoad(true);
        m.texture = GPU::gpu.createTexture("../dino/resource/hero.jpg");
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
        fixture.density = 1.0f;
        fixture.friction = 0.3f;

        body = physics.createBody(&def);

        body->CreateFixture(&fixture);
        b2MassData m;
        m.mass = 1;
        m.center = {0, 0};
        m.I = 0;
        body->SetMassData(&m);
    }

    void update() override
    {
        b2Vec2 pos = body->GetPosition();
        transform.origin = {pos.x, pos.y};

        if (input.getKeyDown(GLFW_KEY_SPACE) && grounded)
        {
            grounded = false;
            body->ApplyForceToCenter({0, 825}, true);
        }
    }

    void onColliderEnter(b2Fixture *other, b2Contact *cnt) override
    {
        if (((Collider *)other->GetBody()->GetUserData().pointer)->id == Collider::ID::GROUND) // if ground
            grounded = true;
        else
            game_over = true;
    }

    void draw() override
    {
        Renderer::setMaterial(m);
        Renderer::setTransform2d(transform.getMatrix());

        Renderer::drawVAO(quad);
    }
};