#include "Scenes.h"

namespace Scene_1
{
    void init()
    {
        scene = new Scene();
        Entity ico_sphere = scene->ecm->add_entity(ENT_TYPE::DEFAULT);
        Entity monkey     = scene->ecm->add_entity(ENT_TYPE::DEFAULT);
        Entity room       = scene->ecm->add_entity(ENT_TYPE::DEFAULT);
        Entity monkey2    = scene->ecm->add_entity(ENT_TYPE::DEFAULT);
        Entity lights     = scene->ecm->add_entity(ENT_TYPE::COMP_GROUP);

        ico_sphere_mat = new MaterialDefault(glm::vec3(1.0f, 1.0f, 1.0f), 0.95f, 0.05f);
        monkey_mat     = new MaterialDefault(glm::vec3(0.9f, 0.1f, 0.9f), 0.95f, 0.05f);
        room_mat       = new MaterialDefault(glm::vec3(0.0f, 0.4f, 1.0f), 0.95f, 0.05f);

        ico_sphere_model = new Mesh("../res/Meshes/ico_sphere_smooth.obj", ico_sphere_mat);
        monkey_model     = new Mesh("../res/Meshes/monkeh.obj", monkey_mat);
        room_model       = new Mesh("../res/Meshes/inverse_cube.obj", room_mat);
        monkey2_model    = new Mesh("../res/Meshes/monkeh.obj", room_mat);

        ico_sphere_model->transform = glm::translate(ico_sphere_model->transform, glm::vec3(-3.0f, 0.0f, 0.0f));
        ico_sphere_model->transform = glm::scale(ico_sphere_model->transform, glm::vec3(1.0f));
        monkey_model->transform = glm::translate(monkey_model->transform, glm::vec3(0.0f, 0.0f, -5.0f));
        room_model->transform = glm::scale(room_model->transform, glm::vec3(1.7f));

        scene->ecm->add_component<Mesh>(ico_sphere, ECPointer<Mesh>(ico_sphere_model));
        scene->ecm->add_component<Mesh>(monkey, ECPointer<Mesh>(monkey_model));
        scene->ecm->add_component<Mesh>(room, ECPointer<Mesh>(room_model));
        scene->ecm->add_component<Mesh>(monkey2, ECPointer<Mesh>(monkey2_model));

        scene->ecm->add_component<PointLight>(lights, PointLight{ 
            .pos = glm::vec3(4.0f, 3.0f, -4.0f),
            .col = glm::vec3(1.0),
            .radius = 1.0f,
            .strength = 5.0f,
            .active = 1
        });
        scene->ecm->add_component<PointLight>(lights, PointLight{ 
            .pos = glm::vec3(-4.0f, 3.0f, -4.0f),
            .col = glm::vec3(1.0f),
            .radius = 0.5f,
            .strength = 8.0f,
            .active = 1
        });
        scene->ecm->add_component<PointLight>(lights, PointLight{ 
            .pos = glm::vec3(-4.0f, 3.0f, 4.0f),
            .col = glm::vec3(1.0f),
            .radius = 0.5f,
            .strength = 8.0f,
            .active = 1
        });
        scene->ecm->add_component<PointLight>(lights, PointLight{ 
            .pos = glm::vec3(4.0f, 3.0f, 4.0f),
            .col = glm::vec3(1.0f),
            .radius = 0.5f,
            .strength = 3.0f,
            .active = 1
        });
    }
}

namespace Scene_2
{
    void init()
    {
        scene = new Scene();
        Entity main_entity = scene->ecm->add_entity(ENT_TYPE::COMP_GROUP);

        bruh_mat = new MaterialDefault(glm::vec3(1.0f, 0.6f, 1.0f), 1.0f, 0.8f);
        main_mesh = new Mesh("../res/Meshes/cube.obj", bruh_mat);
        scene->ecm->add_component<Mesh>(main_entity, ECPointer<Mesh>(main_mesh));
        scene->ecm->add_component<PointLight>(main_entity, PointLight{
            .pos = glm::vec3(1.0f, -1.0f, 3.0f),
            .col = glm::vec3(1.0f),
            .radius = 1.0f,
            .strength = 1.5f,
            .active = 1
        });

    }
}

void init_all_scenes()
{
    Scene_1::init();
    Scene_2::init();
}
