#version 410 core
out vec4 frag_color;

struct PointLight
{
    vec3 pos;
    vec3 col;
    float radius;
    float strength;
    int on;
};

in vec3 tex_coord;
in vec3 normal;
in vec3 frag_pos;
in vec3 view_pos;

uniform PointLight u_lights[8];
uniform sampler2D texture_data1;
uniform sampler2D texture_data2;

uniform vec3 material_color;
uniform float material_diffuse;
uniform float material_specular;

void calc_light_contribution(in PointLight in_light, in vec3 in_view_dir, out vec3 out_contribution)
{
    if (in_light.on == 0)
    {
        out_contribution = vec3(0.0);
        return;
    }

    const int max_spec_power = 64;

    float ambient_term = 0.05; /* Direction agnostic light addition */

    vec3 light_dir = normalize(in_light.pos - frag_pos);
    float diff_coefficient = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff_coefficient * in_light.col * material_diffuse;

    vec3 reflect_dir = reflect(-light_dir, normal);
    int spec_power = int((max_spec_power - 32) * material_specular);
    spec_power += 32;
    float spec = pow(max(dot(in_view_dir, reflect_dir), 0.0), spec_power);
    vec3 specular = spec * in_light.col * material_specular;

    float light_dist = length(in_light.pos - frag_pos) / in_light.radius;
    float light_attentuation = 1.0 / (1.0 + light_dist * light_dist);

    out_contribution = (diffuse + specular) * light_attentuation * in_light.strength;
    out_contribution += ambient_term * in_light.col * light_attentuation;
}

void main()
{
    float contrast = 1.07;
    float brightness = 2.0;
    vec3 view_dir = normalize(view_pos - frag_pos);
    
    vec3 ambient_color = vec3(1.0);
    float ambient_strength = 0.015;
    vec3 ambient = ambient_color * ambient_strength;

    vec3 full_lighting = vec3(0.0);

    for (int i = 0; i < u_lights.length(); i++)
    {
        vec3 contribution = vec3(0.0);
        calc_light_contribution(u_lights[i], view_dir, contribution);
        full_lighting += contribution;
    }

    vec3 dry_color = (full_lighting + ambient) * material_color;
    frag_color = vec4(mix(vec3(0.5, 0.5, 0.5), dry_color * brightness, contrast), 1.0);
} 