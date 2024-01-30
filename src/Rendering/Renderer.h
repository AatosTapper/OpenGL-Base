#pragma once

#include "../config.h"
#include "Objects/VertexArray.h"
#include "Objects/VertexBuffer.h"
#include "Objects/IndexBuffer.h"
#include "Shader/Shader.h"
#include "Objects/Mesh.h"

#include <vector>
#include <memory>

struct QueueObject
{
    const Mesh *mesh;
    const Shader *shader;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void start_frame();
    void end_frame(GLFWwindow *window) const;

    void push_to_queue(const Mesh &mesh, const Shader &shader);
    void draw(const Mesh &mesh, const Shader &shader) const;
    
    void wireframe_on() const;
    void wireframe_off() const;
    void set_arguments(int argc, char** argv);

private:
    std::unique_ptr<std::vector<QueueObject>> m_render_queue;

    void m_draw_queue() const;
};