#include "Engine.h"

#include "../util.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/WindowManager.h"
#include "../Rendering/Objects/Camera.h"
#include "../Rendering/Objects/Mesh.h"
#include "../Rendering/Shader/Shader.h"
#include "../Rendering/Objects/Lights.h"
#include "../Input/CameraController.h"
#include "Scene.h"

Engine::Engine(int argc, char** argv, uint16_t sw, uint16_t sh) : m_active_scene(nullptr)
{
    m_window_manager = std::make_unique<WindowManager>(sw, sh, "Engine");
    m_renderer = std::make_unique<Renderer>();
    m_renderer->set_arguments(argc, argv);
    m_camera = std::make_unique<Camera>(m_window_manager->get_aspect_ratio());
    m_camera_controller = std::make_unique<CameraController>(m_window_manager->get_window(), sw, sh);
}

Engine::~Engine()
{
    m_window_manager->terminate_context();
}

void Engine::load_scene(Scene *active_scene)
{
    ASSERT(active_scene, "Can't load a null scene");
    m_active_scene = active_scene;
}

void Engine::run(const Shader &shader)
{
    ASSERT(m_active_scene, "No active scene found");

    constexpr double tick_speed = 1.0 / 60.0;
    constexpr double fps_limit = 1.0 / 60.0;
    double last_time = glfwGetTime();
    double timer = last_time;
    double tick_delta = 0;
    double fps_delta = 0;
    double now_time = 0;
    uint32_t frames = 0u;
    uint32_t updates = 0u;

    while (!glfwWindowShouldClose(m_window_manager->get_window()))
    {
        glfwPollEvents();

        now_time = glfwGetTime();
        tick_delta += (now_time - last_time) / tick_speed;
        fps_delta += (now_time - last_time) / fps_limit;
        last_time = now_time;

        while (tick_delta >= 1.0)
        {   
            m_update_logic();
            updates++;
            tick_delta--;
        }
        /*
        if (tick_delta > 0.0)
        {
            m_update_logic();
            updates++;
            tick_delta = 0.0;
        }
        */
        //while (fps_delta >= 1.0)
        //{
            m_update_render(shader);
            frames++;
        //    fps_delta--;
        //}
        /*
        if (fps_delta > 0.0)
        {
            m_update_render(shader);
            frames++;
            fps_delta = 0.0;
        }
        */
        
        if (glfwGetTime() - timer > 1.0) 
        {
            timer++;
            LOG("FPS: " << frames << " Updates:" << updates);
            updates = 0, frames = 0;
        }
    }
}

void Engine::m_update_logic()
{
    m_camera_controller->update(m_window_manager->get_window(), *m_camera);
    m_camera->update(m_window_manager->get_aspect_ratio());

    // idk logic or stuff
}

void Engine::m_update_render(const Shader &shader)
{
    m_renderer->start_frame();

    shader.use();
    shader.set_mat4f("u_vp_mat", m_camera->get_vp_matrix());
    shader.set_vec3f("u_view_pos", m_camera->get_position());

    std::vector<PointLight> *lights = m_active_scene->ecm->get_all_components<PointLight>();
    send_lights_to_shader(shader, lights);
    
    std::vector<ECPointer<Mesh>> *ec_meshes = m_active_scene->ecm->get_all_components<ECPointer<Mesh>>();
    for (ECPointer<Mesh> &pointer : *ec_meshes)
    {   
        Mesh *mesh = pointer.ptr;
        //LOG("Mesh ids " << mesh.vao.get_id() << " " << mesh.vbo.get_id());
        shader.set_mat4f("u_transform", mesh->transform);
        shader.set_mat4f("u_inverse_model", glm::transpose(glm::inverse(mesh->transform)));
        m_renderer->draw(*mesh, shader);
    }

    m_renderer->end_frame(m_window_manager->get_window());
}