#include "Renderer.h"

Renderer::Renderer()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Renderer::~Renderer()
{
    
}

void Renderer::start_frame() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::end_frame(GLFWwindow *window) const
{
    glfwSwapBuffers(window);
}

void Renderer::draw(const VertexArray &VAO, const IndexBuffer &EBO, const Shader &shader) const
{
    shader.use();
    VAO.bind();
    glDrawElements(GL_TRIANGLES, EBO.get_elements(), GL_UNSIGNED_INT, 0);
}

void Renderer::wireframe_on() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::wireframe_off() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::settings(int argc, char** argv)
{
    for (uint32_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "wire") == 0)
            wireframe_on();
    }
}
