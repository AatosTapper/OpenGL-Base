#include "Renderer.h"

Renderer::Renderer()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    
}

void Renderer::push_to_queue(const RenderCall *obj)
{
    ASSERT(obj, "Can't push a null object");
    m_render_queue.push_back(obj);
}

void Renderer::start_frame() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_draw_queue();
    m_render_queue.clear();
}

void Renderer::end_frame(GLFWwindow *window) const
{
    glfwSwapBuffers(window);
}

void Renderer::draw(const VertexArray &VAO, const IndexBuffer &EBO, const Shader &shader) const
{
    VAO.bind();
    GL_CHECK();
    EBO.bind();
    GL_CHECK();
    shader.use();
    GL_CHECK();
    glDrawElements(GL_TRIANGLES, EBO.get_elements(), GL_UNSIGNED_INT, 0);
    GL_CHECK();
}

void Renderer::m_draw_queue() const
{
    for (const auto obj : m_render_queue)
    {
        draw(*obj->VAO, *obj->EBO, *obj->shader);
    }
}

void Renderer::wireframe_on() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::wireframe_off() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::set_arguments(int argc, char** argv)
{
    for (uint32_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "wire") == 0)
            wireframe_on();
    }
}
