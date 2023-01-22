#version 330 core

layout (location = 0) in vec3 a_pos;

out vec3 o_tex_coord;
uniform mat4 PVM;

void main()
{
    vec4 pos = PVM * vec4(a_pos, 1.0);
    gl_Position = pos.xyww;

    o_tex_coord = a_pos;
}