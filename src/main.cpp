#include <iostream>
#include <string>
#include "config.h"

#include "Rendering/Renderer.h"
#include "Rendering/WindowManager.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Objects/Lights.h"
#include "Rendering/Objects/Texture.h"
#include "Rendering/Objects/Mesh.h"
#include "Rendering/Objects/Camera.h"
#include "Input/CameraController.h"
#include "Engine/Engine.h"
#include "Engine/Scene.h"

#include <memory>

#define SW 1920
#define SH 1080

int main(int argc, char** argv)
{
    Engine game(argc, argv, SW, SH);
    Scene scene;

    Entity ico_sphere = scene.ecm->add_entity(ENT_TYPE::DEFAULT);
    Entity monkey = scene.ecm->add_entity(ENT_TYPE::DEFAULT);
    Entity room = scene.ecm->add_entity(ENT_TYPE::DEFAULT);

    Mesh ico_sphere_model("../res/Meshes/ico_sphere_smooth.obj");
    Mesh monkey_model("../res/Meshes/monkeh.obj");
    Mesh room_model("../res/Meshes/inverse_cube.obj");

    scene.ecm->add_component<Mesh>(ico_sphere, ECPointer<Mesh>(&ico_sphere_model));
    scene.ecm->add_component<Mesh>(monkey, ECPointer<Mesh>(&monkey_model));
    scene.ecm->add_component<Mesh>(room, ECPointer<Mesh>(&room_model));

    ico_sphere_model.transform = glm::translate(ico_sphere_model.transform, glm::vec3(0.0f, 0.0f, 0.0f));
    ico_sphere_model.transform = glm::scale(ico_sphere_model.transform, glm::vec3(1.0f));
    monkey_model.transform = glm::translate(monkey_model.transform, glm::vec3(0.0f, 0.0f, -5.0f));
    room_model.transform = glm::scale(room_model.transform, glm::vec3(1.7f));
    
    Entity lights = scene.ecm->add_entity(ENT_TYPE::COMP_GROUP);
    scene.ecm->add_component<PointLight>(lights, PointLight{ 
        .pos = glm::vec3(4.0f, 3.0f, -4.0f),
        .col = glm::vec3(0.01f, 0.01f, 1.0f),
        .radius = 1.0f,
        .strength = 4.0f,
        .active = 1
    });
    scene.ecm->add_component<PointLight>(lights, PointLight{ 
        .pos = glm::vec3(-4.0f, 3.0f, -4.0f),
        .col = glm::vec3(1.0f, 0.01f, 0.01f),
        .radius = 0.5f,
        .strength = 8.0f,
        .active = 1
    });
    scene.ecm->add_component<PointLight>(lights, PointLight{ 
        .pos = glm::vec3(-4.0f, 3.0f, 4.0f),
        .col = glm::vec3(1.0f, 1.0f, 1.0f),
        .radius = 0.5f,
        .strength = 8.0f,
        .active = 1
    });
    scene.ecm->add_component<PointLight>(lights, PointLight{ 
        .pos = glm::vec3(4.0f, 3.0f, 4.0f),
        .col = glm::vec3(1.0f, 1.0f, 1.0f),
        .radius = 0.5f,
        .strength = 3.0f,
        .active = 1
    });

    Shader shader("../res/Shaders/default.vert", "../res/Shaders/default.frag");
    
    game.load_scene(&scene);
    game.run(shader);

    return 0;
}
