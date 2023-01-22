#include "image.h"

#include "stb/stb_image.h"
#include <spdlog/spdlog.h>

Image::Image(const char *file)
{
    load(file);
}

void Image::free()
{
    stbi_image_free(data);
}

void Image::setFlipOnLoad(bool f)
{
    stbi_set_flip_vertically_on_load(f);
}

void Image::load(const char *file)
{
    int num_channels;
    data = stbi_load(file, (int *)&width, (int *)&height, &num_channels, 0);

    if (data == nullptr)
        spdlog::error("failed to load image {}\n", file);

    switch (num_channels)
    {
    case 1:
        format = RED;
        return;
    case 2:
        format = RG;
        return;
    case 3:
        format = RGB;
        return;
    case 4:
        format = RGBA;
        return;
    default:
        spdlog::error("invalid number of channels {0}", num_channels);
        return;
    }
}
