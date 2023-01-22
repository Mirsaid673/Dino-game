#include "framebuffer.h"

void Framebuffer::createTexture(const Image &img, Texture::InternalFormat in_f)
{
    texture.create(img, 0, in_f);
    texture.filter(Texture::Filter::LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getID(), 0);
}

void Framebuffer::createRenderbuffer()
{
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void Framebuffer::create(const Image &image, Type t, Texture::InternalFormat in_f)
{
    type = t;
    size.x = image.width;
    size.y = image.height;

    glGenFramebuffers(1, &id);
    bind();

    if (type & Type::TEXRUE)
        createTexture(image, in_f);

    if (type & Type::DEPTH_STENCIL)
        createRenderbuffer();
    createRenderbuffer();

    unbind();
}

void Framebuffer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Framebuffer::readPixels(const glm::ivec2 &coord, const glm::ivec2 &size, uint8_t *data)
{
    bind();
    glReadPixels(coord.x, coord.y, size.x, size.y, texture.getFormat(), texture.getImage().data_type, data);
    unbind();
}

void Framebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Framebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::destroy() const
{
    if (type & Type::TEXRUE)
        texture.destroy();
    if (type & Type::DEPTH_STENCIL)
        glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &id);
}