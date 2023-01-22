#pragma once

#include <GL/glew.h>
#include <stdint.h>

class Image
{
public:
    enum DataType
    {
        BYTE = GL_BYTE,
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        SHORT = GL_SHORT,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        INT = GL_INT,
        UNSIGNED_INT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT,
        TWO_BYTES = GL_2_BYTES,
        THREE_BYTES = GL_3_BYTES,
        FOUR_BYTES = GL_4_BYTES,
        DOUBLE = GL_DOUBLE,
    };

    enum Format
    {
        RED = GL_RED,
        GREEN = GL_GREEN,
        BLUE = GL_BLUE,
        ALPHA = GL_ALPHA,
        RGB = GL_RGB,
        RGBA = GL_RGBA,
        RG = GL_RG,
    };

public:
    void *data = nullptr;

    uint32_t width;
    uint32_t height;

    DataType data_type = UNSIGNED_BYTE;
    Format format = RGB;

public:
    Image() = default;
    Image(const char *file);

    static void setFlipOnLoad(bool f);

    void load(const char *file);
    void free();

    void *getData() const { return data; }
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

    DataType getType() const { return data_type; }
    Format getFormat() const { return format; }
    uint32_t getChanbelNum() const
    {
        switch (format)
        {
        case RED:
        case GREEN:
        case BLUE:
        case ALPHA:
            return 1;
        case RG:
            return 2;
        case RGB:
            return 3;
        case RGBA:
            return 4;
        default:
            return -1;
        }
    }
};