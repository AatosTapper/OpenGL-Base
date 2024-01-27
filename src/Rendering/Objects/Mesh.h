#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct Mesh
{
    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout layout;
    IndexBuffer ebo;
};