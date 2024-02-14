#include "Mesh.h"

#include "../Parsing/ObjParser.h"

Mesh::Mesh(const std::string &obj_file) : transform(glm::mat4(1.0f))
{
    TRACK_PERFORMANCE("Mesh creation for " << obj_file, {

    parse_obj(obj_file, &vbo, &layout, &m_vetex_count);
    vao.add_buffer(vbo, layout);
    GL_CHECK();

    });
}

Mesh::Mesh(const Mesh &old)
{
    LOG("Copied");
    vao = old.vao;
    vbo = old.vbo;
    layout = old.layout;
    transform = old.transform;
    m_vetex_count = old.m_vetex_count;
}

Mesh::~Mesh()
{
    vbo.free();
    vao.free();
}

void Mesh::unbind() const
{
    vao.unbind();
    vbo.unbind();
}

void Mesh::free()
{
    vbo.free();
    vao.free();
}