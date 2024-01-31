#include "Renderer.h"

Renderer::Renderer()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_render_queue = std::make_unique<std::vector<QueueObject>>();
}

Renderer::~Renderer()
{
    
}

void Renderer::push_to_queue(const Mesh &mesh, const Shader &shader)
{
    QueueObject obj = { &mesh, &shader };
    m_render_queue->push_back(obj);
}

void Renderer::start_frame() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_draw_queue();
    m_render_queue->clear();
}

void Renderer::end_frame(GLFWwindow *window) const
{
    glfwSwapBuffers(window);
}

void Renderer::draw(const Mesh &mesh, const Shader &shader) const
{
    mesh.vao.bind();
    GL_CHECK();
    mesh.ebo.bind();
    GL_CHECK();
    shader.use();
    GL_CHECK();
    glDrawElements(GL_TRIANGLES, mesh.ebo.get_elements(), GL_UNSIGNED_INT, 0);
    GL_CHECK();
}

void Renderer::m_draw_queue() const
{
    for (const auto &obj : *m_render_queue)
    {
        ASSERT(obj.mesh && obj.shader, "Object in the draw queue was null");
        draw(*obj.mesh, *obj.shader);
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
        if (strcmp(argv[i], "w") == 0)
            wireframe_on();
    }
}
