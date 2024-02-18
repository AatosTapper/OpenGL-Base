#pragma once

#include "../../config.h"

#include <vector>

class Shader;

struct PointLight
{
    glm::vec3 pos;
    glm::vec3 col;
    float radius;
    float strength;
    int active;
};

void send_lights_to_shader(const Shader &shader, const std::vector<PointLight> *lights);