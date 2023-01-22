#pragma once

#include "../Engine/Core/node.h"
#include "physics.h"

class Ground : public Node, public Collider
{
private:
    RID quad;
    Material m;
    Transform2d transform;
    b2Body *body;

public:
    Ground()
    {
        id = Collider::ID::GROUND;
        glm::vec2 pos = {0, -5};
        glm::vec2 size = {10, 1};

        m.program = &Program::basic2d;
        Image::setFlipOnLoad(true);
        m.texture = GPU::gpu.createTexture("../dino/resource/desk.jpg");
        GPU::gpu.textureFilter(m.texture, Texture::Filter::NEAREST);
        quad = GPU::gpu.getDeafultQuad();

        transform.scale(size);
        transform.origin = pos;

        b2BodyDef def;
        b2BodyUserData data;
        data.pointer = (uintptr_t)((Collider *)this);
        def.userData = data;
        def.position.Set(pos.x, pos.y);

        b2PolygonShape shape;
        shape.SetAsBox(size.x, size.y);

        body = physics.createBody(&def);
        body->CreateFixture(&shape, 0);
    }
    void init() override
    {
    }
    void update() override {}
    void draw() override
    {
        Renderer::setMaterial(m);
        Renderer::setTransform2d(transform.getMatrix());

        Renderer::drawVAO(quad);
    }
};