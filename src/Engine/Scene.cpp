#include "Scene.h"

Scene::Scene()
{
    ecm = std::make_unique<ECManager>();
}

Scene::~Scene()
{

}