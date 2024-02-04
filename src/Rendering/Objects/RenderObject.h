#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

struct RenderObject
{
    std::vector<Mesh*> meshes;
    std::vector<Texture*> textures;
    std::vector<Material*> materials;
};