#pragma once

#include "../Engine/Scene.h"
#include "../Rendering/Shader/Shader.h"
#include "../Rendering/Objects/Lights.h"
#include "../Rendering/Objects/Texture.h"
#include "../Rendering/Objects/Mesh.h"
#include "../Rendering/Objects/Material.h"
#include "../config.h"
#include "../util.h"

namespace Scene_1
{
    inline Scene *scene;
    static MaterialDefault *building_mat;
    static MaterialDefault *landscape_mat;
    static Mesh *building_model;
    static Mesh *landscape_model;
}

namespace Scene_2
{
    inline Scene *scene;
    static MaterialDefault *bruh_mat;
    static Mesh *main_mesh;
}


void init_all_scenes();