#include "Scenes.h"

namespace Scene_1
{
    void init()
    {
        scene = new Scene();
        Entity building = scene->ecm->add_entity(ENT_TYPE::DEFAULT);
        Entity world    = scene->ecm->add_entity(ENT_TYPE::COMP_GROUP);
        Entity lights   = scene->ecm->add_entity(ENT_TYPE::COMP_GROUP);

        building_mat    = new MaterialDefault(glm::vec3(0.7f, 0.6f, 0.5f), 0.9f, 0.6f);
        landscape_mat   = new MaterialDefault(glm::vec3(0.4f, 0.4f, 0.4f), 0.9f, 0.1f);
        landscape_mat->set_albedo("../res/Textures/nerd_face_emoji.jpeg");

        building_model  = new Mesh("../res/Meshes/Buildings.obj", building_mat);
        landscape_model = new Mesh("../res/Meshes/Landscape1.obj", landscape_mat);

        scene->ecm->add_component<Mesh>(building, ECPointer<Mesh>(building_model));
        scene->ecm->add_component<Mesh>(world, ECPointer<Mesh>(landscape_model));
        
        scene->ecm->add_component<PointLight>(lights, PointLight{ 
            .pos = glm::vec3(4.0f, 5.0f, -4.0f),
            .col = glm::vec3(0.0f, 0.05f, 1.0f),
            .radius = 1.4f,
            .strength = 17.0f,
            .active = 1
        });
        /*
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
        */
        scene->ecm->add_component<SunLight>(lights, SunLight{ 
            .dir = glm::vec3(-1.6f, 0.0f, 1.0f),
            .col = glm::vec3(1.0f, 1.0f, 1.0f),
            .strength = 0.12f,
            .active = 1
        });
        scene->ecm->add_component<SunLight>(lights, SunLight{ 
            .dir = glm::vec3(1.2f, 0.8f, -0.3f),
            .col = glm::vec3(1.0f),
            .strength = 0.7f,
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
        bruh_mat->set_albedo("../res/Textures/nerd_face_emoji.jpeg");

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
