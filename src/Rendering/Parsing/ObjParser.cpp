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

    std::vector<float>          vertex_positions;
    std::vector<float>          texture_coordinates;
    std::vector<float>          vertex_normals;
    std::vector<unsigned int>   vertex_indices;
    std::vector<unsigned int>   normal_indices;
    std::vector<unsigned int>   texture_indices;

    
    constexpr uint32_t RESERVE_AMOUNT = 4096; // 2^12 = 4 096
    vertex_positions.reserve(RESERVE_AMOUNT);
    texture_coordinates.reserve(RESERVE_AMOUNT);
    vertex_normals.reserve(RESERVE_AMOUNT);
    vertex_indices.reserve(RESERVE_AMOUNT);
    normal_indices.reserve(RESERVE_AMOUNT);
    texture_indices.reserve(RESERVE_AMOUNT);

    std::stringstream s;
    std::string number;
    float temp[3];
    char line[MAX_LINE_LEN];
    char junk;
    char *curr;
    uint32_t vertex_amount = 0u;
    uint32_t slashes = 0u;

    while (file.getline(line, MAX_LINE_LEN))
    {
        if (line[0] == 'v')
        {
            switch (line[1])
            {
            case ' ': 
            {
                s.clear();
                s.str(line);
                s >> junk >> temp[0] >> temp[1] >> temp[2];
                for (uint32_t i = 0; i < 3; i++)
                {
                    vertex_positions.push_back(temp[i]);
                }
                break;
            }
            case 'n':
            {
                s.clear();
                s.str(line);
                s >> junk >> junk >> temp[0] >> temp[1] >> temp[2];
                for (uint32_t i = 0; i < 3; i++)
                {
                    vertex_normals.push_back(temp[i]);
                }
                break;
            }
            case 't':
            {
                s.clear();
                s.str(line);
                s >> junk >> junk >> temp[0] >> temp[1];
                for (uint32_t i = 0; i < 2; i++)
                {
                    texture_coordinates.push_back(temp[i]);
                }
                break;
            }
            default:
                ASSERT(false, ".obj parsing failed, check the .obj format for " << obj_file);
                break;
            }
        }
        else if (line[0] == 'f')
        {
            curr = &line[1];
            vertex_amount = 0u;
            slashes = 0u;
            while (vertex_amount < 3u && *curr != '\n')
            {
                //LOG("Slashes " << slashes << " V_amount " << vertex_amount << " Curr " << *curr);
                curr++;
                number = "";
                while (isdigit(*curr))
                {
                    number.push_back(*curr);
                    curr++;
                }
                if (!number.empty())
                {
                    switch (slashes)
                    {
                    case 0u:
                        vertex_indices.push_back(static_cast<unsigned int>(std::stoul(number)) - 1u);
                        break;
                    case 1u:
                        texture_indices.push_back(static_cast<unsigned int>(std::stoul(number)) - 1u);
                        break;
                    case 2u:
                        normal_indices.push_back(static_cast<unsigned int>(std::stoul(number)) - 1u);
                        vertex_amount++;
                        slashes = 0u;
                        break;    

                    default:
                        ASSERT(false, ".obj parsing failed, check the .obj format for " << obj_file);
                        break;
                    }
                }
                if (*curr == '/')
                {
                    slashes++;
                }
            }
        }
    }

    
    for (uint32_t i = 0; i < 10; i++)
        LOG("Vert pos: " << vertex_positions[i]);
    
    for (uint32_t i = 0; i < 10; i++)
        LOG("Vert index: " << vertex_indices[i]);
    
    
    out_vbo->set_data((void*)&vertex_positions[0], vertex_positions.size() * sizeof(float));
    GL_CHECK();
    out_ebo->set_data(&vertex_indices[0], vertex_indices.size());
    GL_CHECK();

    out_layout->push<float>(3);
}
