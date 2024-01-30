#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex_coord;

out vec2 tex_coord;

uniform mat4 u_transform;
uniform mat4 u_vp_mat;

void main()
{
    gl_Position = u_vp_mat * u_transform * vec4(aPos, 1.0);
    tex_coord = vec2(aTex_coord.x , aTex_coord.y);
}