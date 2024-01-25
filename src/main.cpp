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

#define SW 1280
#define SH 720

float vertices1[] = {
     0.5f,  0.5f, 1.0f, 1.0f,   // tr
     0.5f, -0.5f, 1.0f, 0.0f,   // br
    -0.5f, -0.5f, 0.0f, 0.0f,   // bl
    -0.5f,  0.5f, 0.0f, 1.0f    // tl
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
    layout.push<float>(2);

    VertexBuffer VBO1;
    VBO1.set_data(vertices1, sizeof(vertices1));

    VertexArray VAO1;
    VAO1.add_buffer(VBO1, layout);

    IndexBuffer EBO;
    EBO.set_data(indices1, 6);

    Texture texture1("../res/Textures/SusRock.jpeg", true);
    Texture texture2("../res/Textures/container.jpg");


    while (!glfwWindowShouldClose(window))
    {
        glActiveTexture(GL_TEXTURE0);
        texture1.bind();

        glActiveTexture(GL_TEXTURE1);
        texture2.bind();

        shader.use();
        shader.set_int("texture_data1", 0);
        shader.set_int("texture_data2", 1);

        renderer.start_frame();
        renderer.draw(VAO1, EBO, shader);
        renderer.end_frame(window);

        glfwPollEvents();
    }

    shader.free();

    EBO.free();
    VBO1.free();
    VAO1.free();
    texture1.free();
    texture2.free();
    
    window_manager.terminate_context();

    return 0;
}
