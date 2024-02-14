#version 410 core
out vec4 frag_color;

in vec3 tex_coord;
in vec3 normal;
in vec3 frag_pos;
in vec3 view_pos;
in vec3 light_pos;

uniform sampler2D texture_data1;
uniform sampler2D texture_data2;

void main()
{
    float light_strength = 1.0;
    float light_radius = 5.0;
    vec3 light_color = vec3(1.0);
    vec3 ambient_color = vec3(1.0);

    float ambient_strength = 0.05;
    vec3 ambient = ambient_color * ambient_strength;

    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff_coefficient = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff_coefficient * light_color;

    float specular_strength = 0.3;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color;

    
    float light_dist = length(light_pos - frag_pos) / light_radius;
    float light_attentuation = 1.0 / (1.0 + light_dist * light_dist);

    vec3 full_lighting = (ambient + diffuse + specular) * light_attentuation * light_strength;

    vec4 obj_color = vec4(0.8, 0.8, 0.8, 1.0);

    frag_color = clamp(vec4(full_lighting, 1.0) * obj_color, 0.0, 1.0);
}