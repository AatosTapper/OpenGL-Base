#pragma once

#include "../config.h"
#include "Objects/VertexArray.h"
#include "Objects/VertexBuffer.h"
#include "Objects/IndexBuffer.h"
#include "Shader/Shader.h"

#include <vector>

struct RenderCall
{
    VertexArray *VAO;
    IndexBuffer *EBO;
    Shader *shader;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void start_frame();
    void end_frame(GLFWwindow *window) const;

    // send object to render at the start of the next render frame
    void push_to_queue(const RenderCall *obj);
    // draw immediately within a render frame
    void draw(const VertexArray &VAO, const IndexBuffer &EBO, const Shader &shader) const;
    
    void wireframe_on() const;
    void wireframe_off() const;
    void set_arguments(int argc, char** argv);

private:
    std::vector<const RenderCall*> m_render_queue;

    void m_draw_queue() const;
};