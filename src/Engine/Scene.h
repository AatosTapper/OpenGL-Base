#pragma once

#include "../config.h"
#include "../util.h"
#include "ECManager.h"
#include "../Rendering/Objects/Mesh.h"

#include <vector>
#include <memory>


class Scene
{
public:
    Scene();
    ~Scene();

    std::unique_ptr<ECManager> ecm;
};