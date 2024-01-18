#pragma once

#include "../config.h"
#include "Objects/VertexArray.h"
#include "Objects/IndexBuffer.h"
#include "Shader/Shader.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void start_frame() const;
    void draw(const VertexArray &VAO, const IndexBuffer &EBO, const Shader &shader) const;
    void end_frame(GLFWwindow *window) const;
    void wireframe_on() const;
    void wireframe_off() const;
    void settings(int argc, char** argv);
};