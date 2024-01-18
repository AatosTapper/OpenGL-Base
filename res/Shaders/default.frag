#version 410 core
out vec4 frag_color;

uniform vec3 rgb_color;

void main()
{
    frag_color = vec4(rgb_color, 1.0);
}