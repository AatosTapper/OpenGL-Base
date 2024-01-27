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
#include "Rendering/Parsing/ObjParser.h"

#define SW 1920
#define SH 1080
#define FOV 85.0f

float vertices1[] = {
    -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,   
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 0.0f, 0.0f,   
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,   
     1.0f, -1.0f,  1.0f, 1.0f, 0.0f,   
     1.0f,  1.0f,  1.0f, 0.0f, 0.0f,   
    -1.0f,  1.0f,  1.0f, 0.0f, 1.0f    
};

unsigned int indices1[] = {
    0, 1, 3, 3, 1, 2,
    1, 5, 2, 2, 5, 6,
    5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3,
    3, 2, 7, 7, 2, 6,
    4, 5, 0, 0, 5, 1
};

int main(int argc, char** argv)
{
    WindowManager window_manager(SW, SH, "OpenGL");
    Renderer renderer;
    renderer.set_arguments(argc, argv);

    GLFWwindow *window = window_manager.get_window();
    
    Shader shader("../res/Shaders/default.vert", "../res/Shaders/default.frag");

    VertexBufferLayout layout;
    layout.push<float>(3);
    GL_CHECK();

    VertexBuffer VBO1;
    IndexBuffer EBO;

    parse_obj("../res/Meshes/SUSobj.obj", &VBO1, &EBO);

    VertexArray VAO1;
    VAO1.add_buffer(VBO1, layout);

    Texture texture1("../res/Textures/container.jpg");

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f));
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.6f));

    while (!glfwWindowShouldClose(window))
    {
        glm::mat4 projection = glm::perspective(glm::radians(FOV), window_manager.get_aspect_ratio(), 0.1f, 1000.0f);
        
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(-1.0f, 1.4f, -1.5f));

        glActiveTexture(GL_TEXTURE0);
        texture1.bind();

        shader.use();
        shader.set_int("texture_data1", 0);
        shader.set_mat4f("model", model);
        shader.set_mat4f("view", view);
        shader.set_mat4f("projection", projection);

        renderer.start_frame();
        glClearColor(0.04f, 0.07f, 0.1f, 1.0f);
        renderer.draw(VAO1, EBO, shader);
        renderer.end_frame(window);

        glfwPollEvents();
    }

    shader.free();

    EBO.free();
    VBO1.free();
    VAO1.free();
    texture1.free();
    
    window_manager.terminate_context();

    return 0;
}
