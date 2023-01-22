#version 330 core

out vec4 out_color;

in vec3 o_tex_coord;

uniform samplerCube tex;

void main()
{
    out_color = texture(tex, o_tex_coord);
}