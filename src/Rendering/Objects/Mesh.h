#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "../Shader/Shader.h"
#include "Material.h"

class Mesh
{
public:
    Mesh(const std::string &obj_file, BaseMaterial *_material);
    Mesh(const Mesh &old);
    ~Mesh();

    void unbind() const;
    void free();
    inline unsigned int get_vertex_count() const { return m_vetex_count; }

    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout layout;
    glm::mat4 transform;
    BaseMaterial *material;

private:
    unsigned int m_vetex_count;
};