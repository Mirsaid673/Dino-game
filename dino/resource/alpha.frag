#version 330 core

out vec4 out_color;

in vec2 o_tex_coord;

uniform sampler2D tex;

void main()
{
    out_color = texture(tex, o_tex_coord);
    if(out_color.a <= 0.1)
        discard;
}