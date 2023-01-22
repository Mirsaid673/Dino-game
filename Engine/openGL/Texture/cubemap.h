#pragma once

#include "texture.h"
#include <array>

class CubeMap
{
private:
    GLuint id = -1;
    uint32_t m_unit = 0;

public:
    CubeMap() = default;

    CubeMap(const std::array<const char *, 6> &files, uint32_t mipmap_levels = 0, bool gamma_correcred = false);
    CubeMap(const std::array<Image, 6> &images, uint32_t mipmap_levels = 0, bool gamma_correcred = false);

    void create(const std::array<const char *, 6> &files, uint32_t mipmap_levels = 0, bool gamma_correcred = false);
    void create(const std::array<Image, 6> &images, uint32_t mipmap_levels = 0, bool gamma_correcred = false);
    void destroy() const;

    void bind() const;
    void unbind() const;
    void use() const;
    void setUnit(uint32_t unit) { m_unit = unit; };

    void wrapMode(Texture::WrapMode wp);
    void filter(Texture::Filter f);
    void mipmaps();
};