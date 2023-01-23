#pragma once

#include "../Engine/Core/application.h"

class Background : public Node
{
    RID quad;
    Material m;
    Transform2d transform;

public:
    void init() override
    {
        quad = GPU::gpu.getDeafultQuad();
        m.program = &Program::basic2d;
        m.texture = GPU::gpu.createTexture("../dino/resource/bg.jpg");
        GPU::gpu.textureFilter(m.texture, Texture::Filter::NEAREST);
        float scale = 5.f;
        transform.scale({scale * 2.0f, scale});
        transform.origin += glm::vec2(0, 1);
    }

    void draw() override
    {
        Renderer::setMaterial(m);
        Renderer::setTransform2d(transform.getMatrix());

        Renderer::drawVAO(quad);
    }
};