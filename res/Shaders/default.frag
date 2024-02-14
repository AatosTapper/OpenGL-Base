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

uniform PointLight u_lights[3];
uniform sampler2D texture_data1;
uniform sampler2D texture_data2;

void calc_light_contribution(in PointLight in_light, in vec3 in_view_dir, out vec3 out_contribution)
{
    if (in_light.on == 0)
    {
        out_contribution = vec3(0.0);
        return;
    }

    vec3 light_dir = normalize(in_light.pos - frag_pos);
    float diff_coefficient = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff_coefficient * in_light.col;

    float specular_strength = 0.3;
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(in_view_dir, reflect_dir), 0.0), 64);
    vec3 specular = specular_strength * spec * in_light.col;

    float light_dist = length(in_light.pos - frag_pos) / in_light.radius;
    float light_attentuation = 1.0 / (1.0 + light_dist * light_dist);

    out_contribution = (diffuse + specular) * light_attentuation * in_light.strength;
}

void main()
{
    vec3 view_dir = normalize(view_pos - frag_pos);
    
    vec3 ambient_color = vec3(1.0);
    float ambient_strength = 0.02;
    vec3 ambient = ambient_color * ambient_strength;

    vec3 full_lighting = vec3(0.0);

    for (int i = 0; i < u_lights.length(); i++)
    {
        vec3 contribution = vec3(0.0);
        calc_light_contribution(u_lights[i], view_dir, contribution);
        full_lighting += contribution;
    }

    vec4 obj_color = vec4(0.8, 0.8, 0.8, 1.0);

    frag_color = clamp(vec4(full_lighting + ambient, 1.0) * obj_color, 0.0, 1.0);
}