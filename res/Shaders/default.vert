#version 410 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec3 a_tex_coord;

out vec3 tex_coord;
out vec3 normal;
out vec3 frag_pos;

uniform mat4 u_transform;
uniform mat4 u_vp_mat;

void main()
{
    gl_Position = u_vp_mat * u_transform * vec4(a_pos, 1.0);
    normal = a_normal;
    tex_coord = a_tex_coord;
    frag_pos = vec3(u_transform * vec4(a_pos, 1.0));
}