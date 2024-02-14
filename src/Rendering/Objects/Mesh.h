#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "../Shader/Shader.h"

class Mesh
{
public:
    Mesh(const std::string &obj_file);
    Mesh(const Mesh &old);
    ~Mesh();

    void unbind() const;
    void free();
    inline unsigned int get_vertex_count() const { return m_vetex_count; }

    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout layout;
    glm::mat4 transform;

private:
    unsigned int m_vetex_count;
};