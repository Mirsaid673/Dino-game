#include "cubemap.h"

CubeMap::CubeMap(const std::array<const char *, 6> &files, uint32_t mipmap_levels, bool gamma_correcred)
{
    create(files, mipmap_levels);
}

CubeMap::CubeMap(const std::array<Image, 6> &images, uint32_t mipmap_levels, bool gamma_correcred)
{
    create(images, mipmap_levels);
}

void CubeMap::create(const std::array<const char *, 6> &files, uint32_t mipmap_levels, bool gamma_correcred)
{
    std::array<Image, 6> images;

    for (int i = 0; i < files.size(); i++)
        images[i].load(files[i]);

    create(images, mipmap_levels);

    for (int i = 0; i < files.size(); i++)
        images[i].free();
}

void CubeMap::create(const std::array<Image, 6> &images, uint32_t mipmap_levels, bool gamma_correcred)
{
    glGenTextures(1, &id);
    bind();

    uint32_t width = images[0].getWidth();
    uint32_t height = images[0].getHeight();

    GLenum internal_format = GL_RGB8;
    if (images[0].getChanbelNum() == 4)
        internal_format = GL_RGBA8;
    if (gamma_correcred)
    {
        if (internal_format == GL_RGB8)
            internal_format = GL_SRGB8;
        else if (internal_format == GL_RGBA8)
            internal_format = GL_SRGB8_ALPHA8;
    }

    glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1 + mipmap_levels, GL_RGB8, width, height);
    for (int i = 0; i < images.size(); i++)
    {
        Image::Format format = images[i].getFormat();
        Image::DataType type = images[i].getType();
        const void *data = images[i].getData();

        glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, width, height, format, type, data);
    }

    unbind();
}

void CubeMap::bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void CubeMap::unbind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::use() const
{
    glActiveTexture(GL_TEXTURE0 + m_unit);
    bind();
}

void CubeMap::destroy() const
{
    glDeleteTextures(1, &id);
}

void CubeMap::wrapMode(Texture::WrapMode wp)
{
    bind();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wp);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wp);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wp);

    unbind();
}

void CubeMap::filter(Texture::Filter f)
{
    bind();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, f);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, f);

    unbind();
}

void CubeMap::mipmaps()
{
    bind();

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    unbind();
}