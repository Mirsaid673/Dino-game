#pragma once

#include "../Engine/Core/application.h"
#include "physics.h"
#include "my_shader.h"

class Dino : public Node, public Collider
{
private:
    RID quad;
    Material m;
    Transform2d transform;
    b2Body *body;
    RID frames[2];
    int frames_count;
    float score_speed = 1.0f;

public:
    float score = 0.0f;
    bool game_over = false;
    bool grounded = true;

    Dino()
    {
        id = Collider::ID::DINO;
        glm::vec2 pos = {-4, -3};
        glm::vec2 size = {1, 1};

        Image::setFlipOnLoad(true);
        frames_count = sizeof(frames) / sizeof(frames[0]);
        frames[0] = GPU::gpu.createTexture("../dino/resource/hero1.png");
        frames[1] = GPU::gpu.createTexture("../dino/resource/hero2.png");
        GPU::gpu.textureFilter(frames[0], Texture::Filter::NEAREST);
        GPU::gpu.textureWrapMode(frames[0], Texture::WrapMode::MIRRORED_REPEAT);
        GPU::gpu.textureFilter(frames[1], Texture::Filter::NEAREST);
        GPU::gpu.textureWrapMode(frames[1], Texture::WrapMode::MIRRORED_REPEAT);
        m.program = &MyShader::program;
        m.texture = frames[0];
        current_frame = 0;
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
        shape.SetAsBox(size.x / 2.0f, size.y - 0.01);

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

    float change_time = 0.2f;
    float time = 0.0f;

    bool impulsed = false;
    void update() override
    {
        body->SetAwake(true);
        b2Vec2 pos = body->GetPosition();
        transform.origin = {pos.x, pos.y};

        score += score_speed * Time::delta_time;
        if (input.getKeyDown(GLFW_KEY_SPACE) && grounded)
        {
            grounded = false;
            impulsed = false;
            body->ApplyForceToCenter({0, 825}, true);
        }
        if (input.getKeyDown(GLFW_KEY_S) && !impulsed)
        {
            impulsed = true;
            body->ApplyForceToCenter({0, -900}, true);
        }

        time += Time::delta_time;
        if (time >= change_time)
        {
            time -= change_time;
            nextFrame();
        }
    }

    void onColliderEnter(b2Fixture *other, b2Contact *cnt) override
    {
        if (((Collider *)other->GetBody()->GetUserData().pointer)->id == Collider::ID::GROUND) // if ground
            grounded = true;
        else
            game_over = true;
    }

    int current_frame;
    void nextFrame()
    {
        m.texture = frames[(current_frame++) % frames_count];
    }

    void draw() override
    {
        Renderer::setMaterial(m);
        Renderer::setTransform2d(transform.getMatrix());

        Renderer::drawVAO(quad);
    }
};