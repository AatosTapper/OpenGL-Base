#include "Scene.h"

#include "../Rendering/Objects/Camera.h"
#include "../Rendering/Objects/Mesh.h"
#include "../Rendering/Objects/Texture.h"
#include "../Rendering/Shader/Shader.h"

Scene::Scene()
{
    meshes = std::make_unique<std::vector<Mesh>>();
    lights = std::make_unique<std::vector<Light>>();
    shaders = std::make_unique<std::vector<Shader>>();
    textures = std::make_unique<std::vector<Texture>>();
}

Scene::~Scene()
{

}