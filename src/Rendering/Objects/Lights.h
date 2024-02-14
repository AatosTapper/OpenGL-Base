#pragma once

#include "../../config.h"

struct PointLight
{
    glm::vec3 pos;
    glm::vec3 col;
    float radius;
    float strength;
    int active;
};
