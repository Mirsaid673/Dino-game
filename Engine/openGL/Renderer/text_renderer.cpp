#include "text_renderer.h"
#include "Program/program.h"
#include "Core/global.h"
#include <spdlog/spdlog.h>

FT_Library TextRenderer::ft;
FT_Face TextRenderer::face;
std::vector<Character> TextRenderer::chars;

void TextRenderer::init()
{
    if (FT_Init_FreeType(&ft))
        spdlog::error("ERROR::FREETYPE: Could not init FreeType Library");
}

void TextRenderer::determinate()
{
    for (auto &c : chars)
        c.texture.destroy();
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::loadFont(const char *file, int size)
{
    if (FT_New_Face(ft, file, 0, &face))
        spdlog::error("ERROR::FREETYPE: Failed to load font");
    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    chars.resize(128);
    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            spdlog::warn("ERROR::FREETYTPE: Failed to load Glyph: {}", c);
            continue;
        }

        Image img;
        img.format = Image::Format::RED;
        img.data_type = Image::DataType::UNSIGNED_BYTE;

        img.width = face->glyph->bitmap.width;
        img.height = face->glyph->bitmap.rows;
        img.data = face->glyph->bitmap.buffer;
        chars[c].bearing.x = face->glyph->bitmap_left;
        chars[c].bearing.y = face->glyph->bitmap_top;
        chars[c].advance = face->glyph->advance.x;
        if (img.width == 0 || img.height == 0)
            continue;
        chars[c].texture.create(img);
        chars[c].texture.filter(Texture::Filter::LINEAR);
        chars[c].texture.wrapMode(Texture::WrapMode::CLAMP_TO_EDGE);
    }
}

void TextRenderer::drawText(const std::string &str, const glm::vec2 &position,const glm::vec3& color, float scale)
{
    Camera2d cam;
    float width = window.getWidth();
    float height = window.getHeight();
    cam.ortho(0, width, 0, height);
    Program::text.use();
    Program::text.setVec3("color",color);

    RID quad = GPU::gpu.getDeafultUIQuad();

    float advance = 0.0f;
    for (int i = 0; i < str.size(); i++)
    {
        char ch = str[i];
        Character c = chars[ch];
        glm::vec2 size = c.texture.getSize();
        Transform2d transform;
        transform.scale(size * scale);
        transform.origin = position + glm::vec2(advance + c.bearing.x, -c.bearing.y) * scale;
        advance +=( c.advance / 64);

        Program::text.setPVM(cam.getProjection() * transform.getMatrix());
        if (c.texture.getID() != -1)
        {
            c.texture.use();
            Renderer::drawVAO(quad);
        }
    }
}