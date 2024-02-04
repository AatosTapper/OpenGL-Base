#pragma once

#include "../config.h"
#include "../util.h"

#include <vector>
#include <memory>

class Mesh;
class Light {};
class Shader;
class Texture;

struct Scene
{
    Scene();
    ~Scene();

    std::unique_ptr<std::vector<Mesh>> meshes;
    std::unique_ptr<std::vector<Light>> lights;
    std::unique_ptr<std::vector<Shader>> shaders;
    std::unique_ptr<std::vector<Texture>> textures;
};