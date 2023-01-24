#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Texture/texture.h"

struct Character
{
    Texture texture;
    glm::ivec2 bearing;
    int advance;
};

class TextRenderer
{
private:
    static FT_Library ft;
    static FT_Face face;
    static std::vector<Character> chars;

public:
    static void init();
    static void determinate();
    static void loadFont(const char *file, int size = 18);
    static void drawText(const std::string &str, const glm::vec2 &pos, const glm::vec3 &color = {0, 0, 0}, float scale = 1);
};