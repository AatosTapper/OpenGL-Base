#version 410 core
out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D texture_data1;
uniform sampler2D texture_data2;
uniform float mix_amount;

void main()
{
    frag_color = mix(texture(texture_data1, tex_coord), texture(texture_data2, tex_coord), mix_amount);
}