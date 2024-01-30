#include "ObjParser.h"

#include "../Objects/VertexBuffer.h"
#include "../Objects/VertexBufferLayout.h"
#include "../Objects/IndexBuffer.h"

#include <fstream>
#include <sstream>
#include <vector>

#define MAX_LINE_LEN 128

// TODO: parse normals and texture coordinates

void parse_obj(const std::string &obj_file, VertexBuffer *out_vbo, IndexBuffer *out_ebo, VertexBufferLayout *out_layout)
{
    std::ifstream file(obj_file);
    ASSERT(file.is_open(), "Failed to load .obj file " << obj_file);

    std::vector<float> vertex_positions;
    std::vector<float> vertex_normals;
    std::vector<unsigned int> index_data;

    vertex_positions.reserve(1024);
    vertex_normals.reserve(1024);
    index_data.reserve(1024);

    while (!file.eof())
    {
        char line[MAX_LINE_LEN];
        file.getline(line, MAX_LINE_LEN);

        char junk;
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
            {
                std::stringstream s;
                s << line;

                float temp[3];
                s >> junk >> temp[0] >> temp[1] >> temp[2];
                for (uint32_t i = 0; i < 3; i++)
                {
                    //LOG("Vertex[" << i << "] = " << temp[i]);
                    vertex_positions.push_back(temp[i]);
                }
            }
            if (line[1] == 'n')
            {
                std::stringstream s;
                s << line;

                float temp[3];
                s >> junk >> temp[0] >> temp[1] >> temp[2];
                for (uint32_t i = 0; i < 3; i++)
                {
                    //LOG("Vertex[" << i << "] = " << temp[i]);
                    vertex_normals.push_back(temp[i]);
                }
            }
        }
        else if (line[0] == 'f' && line[1] == ' ')
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

    out_vbo->set_data((void*)&vertex_positions[0], vertex_positions.size() * sizeof(float));
    GL_CHECK();
    out_ebo->set_data(&index_data[0], index_data.size());
    GL_CHECK();

    out_layout->push<float>(3);
}
