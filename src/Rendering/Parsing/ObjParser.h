#pragma once

#include "../../config.h"
#include "../../util.h"

#include <string>

class VertexBuffer;
class IndexBuffer;
class VertexBufferLayout;

void parse_obj(const std::string &obj_file, VertexBuffer *out_vbo, IndexBuffer *out_ebo, VertexBufferLayout *out_layout);