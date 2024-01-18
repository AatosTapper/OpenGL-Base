#include <iostream>
#include <string>
#include "config.h"

#include "Rendering/Renderer.h"
#include "Rendering/WindowManager.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Objects/VertexBuffer.h"
#include "Rendering/Objects/VertexArray.h"
#include "Rendering/Objects/IndexBuffer.h"

#define SW 1280
#define SH 720

float vertices[] = {
     0.7f,  0.7f, // tr
     0.7f, -0.7f, // br
    -0.7f, -0.7f,  // bl
    -0.7f,  0.7f// tl
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main(int argc, char** argv)
{
    WindowManager window_manager(SW, SH, "OpenGL");
    Renderer renderer;
    renderer.settings(argc, argv);

    GLFWwindow *window = window_manager.get_window();
    
    Shader shader("../res/Shaders/default.vert", "../res/Shaders/default.frag");

    VertexBuffer VBO;
    VBO.set_data(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.push<float>(2);

    VertexArray VAO;
    VAO.add_buffer(VBO, layout);

    IndexBuffer EBO;
    EBO.set_data(indices, 6);

    while (!glfwWindowShouldClose(window))
    {
        float time_val = glfwGetTime();
        float red = sin(time_val);
        float green = sin(time_val + PI);
        float blue = sin(2 * time_val + PI / 2);

        shader.use();
        shader.set_3f("rgb_color", red, green, blue);

        renderer.start_frame();
        renderer.draw(VAO, EBO, shader);
        renderer.end_frame(window);
        glfwPollEvents();
    }

    shader.free();
    VBO.free();
    EBO.free();
    VAO.free();
    
    window_manager.terminate_context();

    return 0;
}
