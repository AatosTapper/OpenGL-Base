#include "Mesh.h"

#include "../Parsing/ObjParser.h"

Mesh::Mesh(const std::string &obj_file) : model(glm::mat4(1.0f))
{
    TRACK_PERFORMANCE("Mesh creation for " << obj_file, {

    parse_obj(obj_file, &vbo, &ebo, &layout);
    vao.add_buffer(vbo, layout);
    GL_CHECK();

    });
}

Mesh::~Mesh()
{
    ebo.free();
    vbo.free();
    vao.free();
}

void Mesh::free()
{
    ebo.free();
    vbo.free();
    vao.free();
}