#version 330 core

layout (location = 5) in vec2 a_pos;
layout (location = 2) in vec3 a_color;

out vec3 o_color;

uniform mat3 PVM;

void main()
{
    gl_Position = vec4(PVM * vec3(a_pos, 1), 1);
    o_color = a_color;
}