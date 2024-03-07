#pragma once

#include "../../config.h"

#include <vector>

class Shader;

#define POINT_LIGHT_STRIDE 5
struct PointLight
{
    glm::vec3 pos;
    glm::vec3 col;
    float radius;
    float strength;
    int active;
};

#define SUN_LIGHT_STRIDE 4
struct SunLight
{
    glm::vec3 dir;
    glm::vec3 col;
    float strength;
    int active;
};

void send_lights_to_shader(const Shader *shader, const std::vector<PointLight> *lights);
void send_lights_to_shader(const Shader *shader, const std::vector<SunLight> *lights);