#version 410 core
out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D texture_data1;
uniform sampler2D texture_data2;

void main()
{
    frag_color = vec4(0.5, 0.5, 0.5, 1.0);
}