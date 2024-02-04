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

Mesh::~Mesh()
{
    vbo.free();
    vao.free();
}

void Mesh::free()
{
    vbo.free();
    vao.free();
}