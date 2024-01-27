#include "ObjParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#define MAX_LINE_LEN 256

void parse_obj(const std::string &obj_file, VertexBuffer *out_vbo, IndexBuffer *out_ebo)
{
    std::ifstream file(obj_file);
    ASSERT(file.is_open(), "Failed to load .obj file " << obj_file);

    std::vector<float> vertex_data;
    std::vector<unsigned int> index_data;

    while (!file.eof())
    {
        char line[MAX_LINE_LEN];
        file.getline(line, MAX_LINE_LEN);

        char junk;
        if (line[0] == 'v' && line[1] == ' ')
        {
            std::stringstream s;
            s << line;

            float temp[3];
            s >> junk >> temp[0] >> temp[1] >> temp[2];
            for (uint32_t i = 0; i < 3; i++)
            {
                //LOG("Vertex[" << i << "] = " << temp[i]);
                vertex_data.push_back(temp[i]);
            }
        }

        if (line[0] == 'f' && line[1] == ' ')
        {
            char *curr = &line[1];
            uint32_t num_amount = 0;
            while (num_amount < 6)
            {
                std::string number;
                while (isdigit(*curr))
                {
                    number.push_back(*curr);
                    curr++;
                }

                if (number != "")
                {
                    num_amount++;
                    if (num_amount % 2 == 1) // discard texture coordinates
                    {
                        //LOG("Index " << number);
                        index_data.push_back(static_cast<unsigned int>(std::stoul(number)) - 1u);
                    }
                }
                curr++;
            }
        }
    }

    out_vbo->set_data((void*)&vertex_data[0], vertex_data.size() * sizeof(float));
    GL_CHECK();
    out_ebo->set_data(&index_data[0], index_data.size());
    GL_CHECK();
}

Mesh create_mesh(const std::string &obj_file)
{
    VertexBuffer vbo;
    IndexBuffer ebo;
    parse_obj(obj_file, &vbo, &ebo);

    VertexBufferLayout layout;
    layout.push<float>(3);

    VertexArray vao;
    vao.add_buffer(vbo, layout);
    GL_CHECK();

    return { vao, vbo, layout, ebo };
}