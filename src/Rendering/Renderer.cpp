#include "Renderer.h"

Renderer::Renderer()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    //WARN("Backface culling disabled");
    glEnable(GL_FRAMEBUFFER_SRGB);
    WARN("Built in gamma correction enabled");
}

Renderer::~Renderer()
{
    
}

void Renderer::start_frame() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::end_frame(GLFWwindow *window) const
{
    glfwSwapBuffers(window);
}

// This is shit, because each vertex is unique but normals don't work otherwise so...
void Renderer::draw(const Mesh &mesh) const
{
    mesh.vao.bind();
    //mesh.ebo.bind();
    //glDrawElements(GL_TRIANGLES, mesh.ebo.get_elements(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, mesh.get_vertex_count());
    GL_CHECK();
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
