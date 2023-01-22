#version 330 core

out vec4 out_color;

in vec3 o_color;

uniform sampler2D tex;

void main()
{
    out_color = vec4(o_color, 1);
}