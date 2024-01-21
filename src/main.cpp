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

float vertices1[] = {
     0.8f,  0.7f, // tr
     0.8f, -0.7f, // br
     0.4f, -0.7f,  // bl
     0.4f,  0.7f// tl
};

unsigned int indices1[] = {
    0, 1, 3,
    1, 2, 3
};

int main(int argc, char** argv)
{
    WindowManager window_manager(SW, SH, "OpenGL");
    Renderer renderer;
    renderer.set_arguments(argc, argv);

    GLFWwindow *window = window_manager.get_window();
    
    Shader shader("../res/Shaders/default.vert", "../res/Shaders/default.frag");

    VertexBufferLayout layout;
    layout.push<float>(2);

    VertexBuffer VBO1;
    VBO1.set_data(vertices1, sizeof(vertices1));

    VertexArray VAO1;
    VAO1.add_buffer(VBO1, layout);

    IndexBuffer EBO;
    EBO.set_data(indices1, 6);

    RenderCall obj1 = { &VAO1, &EBO, &shader };

    while (!glfwWindowShouldClose(window))
    {
        float time_val = glfwGetTime();
        float red = sin(time_val);
        float green = sin(time_val + PI);
        float blue = sin(2 * time_val + PI / 2);

        shader.use();
        shader.set_3f("rgb_color", red, green, blue);

        // somewhere in application logic
        renderer.push_to_queue(&obj1);

        // rendering happens here
        renderer.start_frame();
        renderer.end_frame(window);

        glfwPollEvents();
    }

    shader.free();

    EBO.free();
    VBO1.free();
    VAO1.free();
    
    window_manager.terminate_context();

    return 0;
}
