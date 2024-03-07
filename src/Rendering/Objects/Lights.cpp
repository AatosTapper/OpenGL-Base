#include "Lights.h"

#include "../../util.h"
#include "../Shader/Shader.h"

void send_lights_to_shader(const Shader *shader, const std::vector<PointLight> *lights)
{
    if (lights == nullptr) return;
    
    const uint32_t max_lights = 8;
    uint32_t ligts_size = lights->size() > max_lights ? max_lights : lights->size();

    GLint uniform_location = shader->get_location("u_point_lights[0].pos");
    for (uint32_t i = 0; i < ligts_size; i++)
    {
        glUniform3fv(uniform_location + POINT_LIGHT_STRIDE * i, 1, glm::value_ptr(lights->at(i).pos));
        glUniform3fv(uniform_location + POINT_LIGHT_STRIDE * i + 1, 1, glm::value_ptr(lights->at(i).col));
        glUniform1f(uniform_location + POINT_LIGHT_STRIDE * i + 2, lights->at(i).radius);
        glUniform1f(uniform_location + POINT_LIGHT_STRIDE * i + 3, lights->at(i).strength);
        glUniform1i(uniform_location + POINT_LIGHT_STRIDE * i + 4, lights->at(i).active);
    }
}

void send_lights_to_shader(const Shader *shader, const std::vector<SunLight> *lights)
{
    if (lights == nullptr) return;

    const uint32_t max_lights = 8;
    uint32_t ligts_size = lights->size() > max_lights ? max_lights : lights->size();
    //LOG_VARIABLE(ligts_size);
    GLint uniform_location = shader->get_location("u_sun_lights[0].dir");
    for (uint32_t i = 0; i < ligts_size; i++)
    {
        glUniform3fv(uniform_location + SUN_LIGHT_STRIDE * i, 1, glm::value_ptr(lights->at(i).dir));
        glUniform3fv(uniform_location + SUN_LIGHT_STRIDE * i + 1, 1, glm::value_ptr(lights->at(i).col));
        glUniform1f(uniform_location + SUN_LIGHT_STRIDE * i + 2, lights->at(i).strength);
        glUniform1i(uniform_location + SUN_LIGHT_STRIDE * i + 3, lights->at(i).active);
    }
}