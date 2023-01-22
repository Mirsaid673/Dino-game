#include "texture.h"

Texture::Texture(const Image &image, uint32_t mipmap_levels, InternalFormat internal_format)
{
    create(image, mipmap_levels, internal_format);
}

Texture::Texture(const char *file, uint32_t mipmap_levels, InternalFormat internal_format)
{
    create(file, mipmap_levels, internal_format);
}

void Texture::create(const char *file, uint32_t mipmap_levels, InternalFormat internal_format)
{
    Image im(file);

    create(im, mipmap_levels, internal_format);
    im.free();
}

void Texture::create(const Image &i, uint32_t mipmap_levels, InternalFormat internal_format)
{
    img = i;
    this->internal_format = internal_format;
    glGenTextures(1, &id);
    bind();

    uint32_t width = i.getWidth();
    uint32_t height = i.getHeight();

    glTexStorage2D(GL_TEXTURE_2D, 1 + mipmap_levels, getImageInternalFormat(internal_format), width, height);
    if (i.getData())
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, i.getFormat(), i.getType(), i.getData());

    unbind();
}

void Texture::subimage(const glm::ivec2 &coord, const glm::ivec2 &size, uint8_t *data)
{
    bind();
    glTexSubImage2D(GL_TEXTURE_2D, 0, coord.x, coord.y, size.x, size.y, getFormat(), img.getType(), data);
}

void Texture::destroy() const
{
    glDeleteTextures(1, &id);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::use() const
{
    glActiveTexture(GL_TEXTURE0 + m_unit);
    bind();
}

void Texture::wrapMode(WrapMode wp) const
{
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);

    unbind();
}

void Texture::filter(Filter f) const
{
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);

    unbind();
}

void Texture::mipmaps() const
{
    bind();

    glGenerateMipmap(GL_TEXTURE_2D);

    unbind();
}