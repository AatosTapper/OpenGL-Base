#version 410 core
out vec4 frag_color;

in vec3 tex_coord;
in vec3 normal;
in vec3 frag_pos;

uniform sampler2D texture_data1;
uniform sampler2D texture_data2;

void main()
{
    vec3 light_pos = vec3(1.0, 1.0, -3.0);
    vec3 light_color = vec3(0.9, 1.0, 1.0);

    float ambient_strenght = 0.1;
    vec3 ambient = light_color * ambient_strenght;

    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff_coefficient = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff_coefficient * light_color;

    vec4 obj_color = texture(texture_data1, vec2(tex_coord.x, tex_coord.y));

    frag_color = vec4((ambient + diffuse), 1.0) * obj_color;
}