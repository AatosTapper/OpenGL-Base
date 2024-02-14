#pragma once

#include "../config.h"
#include "Objects/VertexArray.h"
#include "Objects/VertexBuffer.h"
#include "Objects/IndexBuffer.h"
#include "Shader/Shader.h"
#include "Objects/Mesh.h"

#include <vector>
#include <memory>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void start_frame();
    void end_frame(GLFWwindow *window) const;

    void draw(const Mesh &mesh, const Shader &shader) const;
    
    void wireframe_on() const;
    void wireframe_off() const;
    void set_arguments(int argc, char** argv);
};