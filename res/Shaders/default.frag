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

struct SunLight
{
    vec3 dir;
    vec3 col;
    float strength;
    int on;
};

in vec3 tex_coord;
in vec3 normal;
in vec3 frag_pos;
in vec3 view_pos;

uniform PointLight u_point_lights[8];
uniform SunLight u_sun_lights[8];

uniform sampler2D u_albedo_1;
uniform sampler2D texture_data2;

uniform vec3 material_color;
uniform float material_diffuse;
uniform float material_specular;

vec3 point_light_contribution(in PointLight in_light, in vec3 in_view_dir)
{
    vec3 out_contribution = vec3(0.0);
    if (in_light.on == 0)
    {
        return out_contribution;
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
    return out_contribution;
}

vec3 sun_light_contribution(in SunLight in_light, in vec3 in_view_dir)
{
    if (in_light.on == 0)
    {
        return vec3(0.0);
    }

    const int max_spec_power = 64;

    vec3 light_dir = normalize(in_light.dir);
    float diff_coefficient = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff_coefficient * in_light.col * material_diffuse;

    vec3 reflect_dir = reflect(-light_dir, normal);
    int spec_power = int((max_spec_power - 32) * material_specular);
    spec_power += 32;
    float spec = pow(max(dot(in_view_dir, reflect_dir), 0.0), spec_power);
    vec3 specular = spec * in_light.col * material_specular;

    return (diffuse + specular) * in_light.strength;
}

void main()
{
    float contrast = 1.07;
    float brightness = 2.0;
    vec3 view_dir = normalize(view_pos - frag_pos);
    
    vec3 ambient_color = vec3(1.0);
    float ambient_strength = 0.01;
    vec3 ambient = ambient_color * ambient_strength;

    vec3 full_lighting = vec3(0.0);

    for (int i = 0; i < u_point_lights.length(); i++)
    {
        full_lighting += point_light_contribution(u_point_lights[i], view_dir);
    }

    for (int i = 0; i < u_sun_lights.length(); i++)
    {
        full_lighting += sun_light_contribution(u_sun_lights[i], view_dir);
    }
    
    vec3 flat_color = material_color * texture(u_albedo_1, tex_coord.xy).xyz;
    vec3 lit_color = (full_lighting + ambient) * flat_color;
    frag_color = vec4(mix(vec3(0.5, 0.5, 0.5), lit_color * brightness, contrast), 1.0);
}
