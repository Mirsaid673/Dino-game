#version 330 core

layout (location = 5) in vec2 a_pos;
layout (location = 3) in vec2 a_tex_coord;

out vec2 o_tex_coord;


void main()
{
    gl_Position =  vec4(a_pos, 0, 1);
    o_tex_coord = a_tex_coord;
}