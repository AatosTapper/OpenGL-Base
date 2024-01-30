#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../Shader/Shader.h"

// This is stupid object oriented but will stay for a while

// TODO: replace with ordered component rendering, where mesh is just an index

class Mesh
{
public:
    Mesh(const std::string &obj_file);
    ~Mesh();

    void free();

    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout layout;
    IndexBuffer ebo;
    glm::mat4 model;
};