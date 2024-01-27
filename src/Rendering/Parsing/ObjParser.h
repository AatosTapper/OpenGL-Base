#pragma once

#include "../../config.h"
#include "../../util.h"
#include "../Objects/Mesh.h"

#include <string>

void parse_obj(const std::string &obj_file, VertexBuffer *out_vbo, IndexBuffer *out_ebo);
Mesh create_mesh(const std::string &obj_file);