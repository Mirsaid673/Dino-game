#pragma once

#include "Texture/texture.h"
#include <glm/glm.hpp>

class Framebuffer
{
public:
    enum Type : uint8_t
    {
        TEXRUE = 1 << 0,
        DEPTH = 1 << 1,
        STENCIL = 1 << 2,

        DEPTH_STENCIL = DEPTH | STENCIL,
        TEXRUE_DEPTH = TEXRUE | DEPTH,
        TEXRUE_STENCIL = TEXRUE | STENCIL,
        TEXRUE_DEPTH_STENCIL = TEXRUE | DEPTH | STENCIL,
    };

private:
    glm::ivec2 size;
    Texture texture;
    GLuint id = -1;
    GLuint rbo = -1;
    Type type;

public:
    Framebuffer() = default;

    void create(const Image& image, Type type = TEXRUE_DEPTH_STENCIL, Texture::InternalFormat in_f = Texture::InternalFormat::NOTHING);
    void clear() const;
    void readPixels(const glm::ivec2& coord, const glm::ivec2& size, uint8_t* data);

    void bind() const;
    void unbind() const;
    void destroy() const;

    void resize(int w, int h);
    const glm::ivec2 &getSize() const { return size; }
    const Texture &getTexture() const { return texture; }
    Texture &getTexture() { return texture; }

private:
    void createTexture(const Image& img, Texture::InternalFormat in_f);
    void createRenderbuffer();

public:
    static void bindMain() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
};