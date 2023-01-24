#version 330 core

out vec4 out_color;

in vec2 o_tex_coord;

uniform sampler2D tex;

uniform vec3 color;

void main()
{
    if(texture(tex, o_tex_coord).r < 0.1)
        discard;
    out_color = vec4(color, 1);
}