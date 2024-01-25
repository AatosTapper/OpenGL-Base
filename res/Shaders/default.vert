#version 410 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex_coord;

out vec2 tex_coord;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    tex_coord = aTex_coord;
}