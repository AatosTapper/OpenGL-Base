#include "Lights.h"

#include "../Shader/Shader.h"

void send_lights_to_shader(const Shader *shader, const std::vector<PointLight> *lights)
{
    const uint32_t max_lights = 8;
    uint32_t ligts_size = lights->size() > max_lights ? max_lights : lights->size();

    GLint uniform_location = shader->get_location("u_lights[0].pos");
    for (uint32_t i = 0; i < ligts_size; i++)
    {
        glUniform3fv(uniform_location + 5 * i, 1, glm::value_ptr(lights->at(i).pos));
        glUniform3fv(uniform_location + 5 * i + 1, 1, glm::value_ptr(lights->at(i).col));
        glUniform1f(uniform_location + 5 * i + 2, lights->at(i).radius);
        glUniform1f(uniform_location + 5 * i + 3, lights->at(i).strength);
        glUniform1i(uniform_location + 5 * i + 4, lights->at(i).active);
    }
}