#version 410 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex_coord;

out vec2 tex_coord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 0.0, 1.0);
    tex_coord = vec2(aTex_coord.x , aTex_coord.y);
}