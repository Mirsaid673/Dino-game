#pragma once

#include "Resources/image.h"
#include <glm/glm.hpp>
#include "utils.h"

class Texture
{
public:
    enum WrapMode
    {
        REPEAT = GL_REPEAT,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        CLAMP = GL_CLAMP,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    };

    enum Filter
    {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR,

        NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
        LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
    };

    enum InternalFormat
    {
        NOTHING,
        GAMMA_CORRECTED,
        INTEGER,
        UINTEGER,
    };

private:
    Image img;
    GLuint id = -1;
    uint32_t m_unit = 0;
    InternalFormat internal_format;

public:
    Texture() = default;
    Texture(const Image &image, uint32_t mipmap_levels = 0, InternalFormat internal_format = NOTHING);
    Texture(const char *file, uint32_t mipmap_levels = 0, InternalFormat internal_format = NOTHING);

    void create(const char *file, uint32_t mipmap_levels = 0, InternalFormat internal_format = NOTHING);
    void create(const Image &image, uint32_t mipmap_levels = 0, InternalFormat internal_format = NOTHING);
    void destroy() const;

    void bind() const;
    void unbind() const;
    void use() const;
    void setUnit(uint32_t unit) { m_unit = unit; };
    void subimage(const glm::ivec2 &coord, const glm::ivec2 &size, uint8_t *data);

    void wrapMode(WrapMode wp) const;
    void filter(Filter f) const;
    void mipmaps() const;

    GLuint getID() const { return id; }
    const Image &getImage() const { return img; }

public:
    GLenum getImageInternalFormat(InternalFormat in_f)
    {
        switch (in_f)
        {
        case InternalFormat::NOTHING:
            return getInternalFormat();
        case InternalFormat::INTEGER:
            return getInternalFormatInteger();
        case InternalFormat::UINTEGER:
            return getInternalFormatUInteger();
        case InternalFormat::GAMMA_CORRECTED:
            return getInternalFormatGammaCorrected();
        }
        return GL_RGB8;
    }

private:
    GLenum getInternalFormat()
    {
        switch (img.format)
        {
        case Image::Format::RED:
        case Image::Format::GREEN:
        case Image::Format::BLUE:
        case Image::Format::ALPHA:
            return GL_R8;
        case Image::Format::RG:
            return GL_RG8;
        case Image::Format::RGB:
            return GL_RGB8;
        case Image::Format::RGBA:
            return GL_RGBA8;
        }
        return GL_RGB8;
    }
    GLenum getInternalFormatInteger()
    {
        switch (img.format)
        {
        case Image::Format::RED:
        case Image::Format::GREEN:
        case Image::Format::BLUE:
        case Image::Format::ALPHA:
            return GL_R8I;
        case Image::Format::RG:
            return GL_RG8I;
        case Image::Format::RGB:
            return GL_RGB8I;
        case Image::Format::RGBA:
            return GL_RGBA8I;
        }
        return GL_RGB8;
    }
    GLenum getInternalFormatUInteger()
    {
        switch (img.format)
        {
        case Image::Format::RED:
        case Image::Format::GREEN:
        case Image::Format::BLUE:
        case Image::Format::ALPHA:
            return GL_R8UI;
        case Image::Format::RG:
            return GL_RG8UI;
        case Image::Format::RGB:
            return GL_RGB8UI;
        case Image::Format::RGBA:
            return GL_RGBA8UI;
        }
        return GL_RGB8;
    }
    GLenum getInternalFormatGammaCorrected()
    {
        switch (img.format)
        {
        case Image::Format::RGB:
            return GL_SRGB8;
        case Image::Format::RGBA:
            return GL_SRGB8_ALPHA8;
        }
        spdlog::error("non rgb(a) format cannot be gamma corrected!");
        return GL_RGB8;
    }

public:
    GLenum getFormat()
    {
        if (internal_format == InternalFormat::INTEGER || internal_format == InternalFormat::UINTEGER)
        {
            switch (img.format)
            {
            case Image::Format::RED:
                return GL_RED_INTEGER;
            case Image::Format::GREEN:
                return GL_GREEN_INTEGER;
            case Image::Format::BLUE:
                return GL_BLUE_INTEGER;
            case Image::Format::ALPHA:
                return GL_ALPHA_INTEGER;
            case Image::Format::RG:
                return GL_RG_INTEGER;
            case Image::Format::RGB:
                return GL_RGB_INTEGER;
            case Image::Format::RGBA:
                return GL_RGBA_INTEGER;
            }
        }
        return img.format;
    }

    friend class Renderer;
};