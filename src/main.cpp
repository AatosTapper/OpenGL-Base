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

#define SW 1280
#define SH 720

int main(int argc, char** argv)
{
    WindowManager window_manager(SW, SH, "OpenGL");
    GLFWwindow *window = window_manager.get_window();
    Renderer renderer;
    renderer.set_arguments(argc, argv);
    CameraController camera_controller(window, SW, SH);
    
    Shader shader("../res/Shaders/default.vert", "../res/Shaders/default.frag");
    
    Mesh monkeh("../res/Meshes/monkeh.obj");
    Mesh monkeh2("../res/Meshes/round_cube.obj");
    Mesh torus("../res/Meshes/monkeh.obj");

    Texture texture1("../res/Textures/container.jpg");

    monkeh.model = glm::translate(monkeh.model, glm::vec3(-6.0f, 4.0f, 0.0f));
    monkeh2.model = glm::translate(monkeh2.model, glm::vec3(0.0f, -5.0f, -4.0f));
    torus.model = glm::translate(torus.model, glm::vec3(-1.0f, 0.5f, -3.0f));
    torus.model = glm::scale(torus.model, glm::vec3(0.5f));

    Camera camera(window_manager.get_aspect_ratio());

    constexpr double tick_speed = 1.0 / 60.0;
    constexpr double fps_limit = 1.0 / 60.0;
    double last_time = glfwGetTime();
    double timer = last_time;
    double tick_delta = 0;
    double fps_delta = 0;
    double now_time = 0;
    uint32_t frames = 0;
    uint32_t updates = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        now_time = glfwGetTime();
        tick_delta += (now_time - last_time) / tick_speed;
        fps_delta += (now_time - last_time) / fps_limit;
        last_time = now_time;

        while (tick_delta >= 1.0)
        {
            camera_controller.update(window, camera);
            camera.update(window_manager.get_aspect_ratio());

            updates++;
            tick_delta--;
        }
        //while (fps_delta >= 1.0)
        {
            renderer.start_frame();

            glActiveTexture(GL_TEXTURE0);
            texture1.bind();

            shader.use();
            shader.set_int("texture_data1", 0);
            shader.set_mat4f("u_vp_mat", camera.get_vp_matrix());

            glClearColor(0.04f, 0.07f, 0.1f, 1.0f);
            shader.set_mat4f("u_transform", monkeh.model);
            renderer.draw(monkeh, shader);

            shader.set_mat4f("u_transform", monkeh2.model);
            renderer.draw(monkeh2, shader);

            shader.set_mat4f("u_transform", torus.model);
            renderer.draw(torus, shader);
            renderer.end_frame(window);

            frames++;
            //fps_delta--;
        }
        
        if (glfwGetTime() - timer > 1.0) 
        {
            timer++;
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
        }
    }

    monkeh.free();
    torus.free();
    texture1.free();
    
    window_manager.terminate_context();

    return 0;
}
