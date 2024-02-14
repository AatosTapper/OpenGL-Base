#pragma once

#include "Mesh.h"
#include "Material.h"

struct RenderObject
{
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
    glm::mat4 transform;
};