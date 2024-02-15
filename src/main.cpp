#include <iostream>
#include <string>
#include "config.h"

#include "Rendering/Renderer.h"
#include "Rendering/WindowManager.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Objects/VertexBuffer.h"
#include "Rendering/Objects/VertexArray.h"
#include "Rendering/Objects/IndexBuffer.h"
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
    Entity sus = scene.ecm->add_entity(ENT_TYPE::DEFAULT);
    
    scene.ecm->add_component<Mesh>(ico_sphere, ECPointer<Mesh>(new Mesh("../res/Meshes/monkeh.obj")));
    scene.ecm->add_component<Mesh>(monkey, ECPointer<Mesh>(new Mesh("../res/Meshes/monkeh.obj")));
    scene.ecm->add_component<Mesh>(room, ECPointer<Mesh>(new Mesh("../res/Meshes/inverse_cube.obj")));
    scene.ecm->add_component<Mesh>(sus, ECPointer<Mesh>(new Mesh("../res/Meshes/monkeh.obj")));
    
    Mesh *ico_sphere_model = scene.ecm->get_component<ECPointer<Mesh>>(ico_sphere)->ptr;
    Mesh *monkey_model = scene.ecm->get_component<ECPointer<Mesh>>(monkey)->ptr;
    Mesh *room_model = scene.ecm->get_component<ECPointer<Mesh>>(room)->ptr;

    ico_sphere_model->transform = glm::translate(ico_sphere_model->transform, glm::vec3(-5.0f, 3.0f, -4.0f));
    monkey_model->transform = glm::translate(monkey_model->transform, glm::vec3(0.0f, 0.0f, -5.0f));
    room_model->transform = glm::scale(room_model->transform, glm::vec3(1.5f));

    Shader shader("../res/Shaders/default.vert", "../res/Shaders/default.frag");
    
    game.load_scene(&scene);
    
    game.run(shader);

    return 0;
}
