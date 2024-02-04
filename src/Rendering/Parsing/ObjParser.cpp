#include "ObjParser.h"

// ----------------------------- WARNING -----------------------------
// This file is kinda trash but it works well enough and somewhat fast

#include "../Objects/VertexBuffer.h"
#include "../Objects/VertexBufferLayout.h"
#include "../Objects/IndexBuffer.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define MAX_LINE_LEN 128

struct FullIndex
{
    unsigned int position;
    unsigned int texture;
    unsigned int normal;
};

#define VEC(x, y, z) {{ x, y, z }}
#define NULL_VEC VEC(0.0f, 0.0f, 0.0f)
struct Vec3f
{
    float data[3] = { 0.0f, 0.0f, 0.0f };
};

void parse_obj(const std::string &obj_file, VertexBuffer *out_vbo, VertexBufferLayout *out_layout, unsigned int *out_count)
{
    std::ifstream file(obj_file);
    ASSERT(file.is_open(), "Failed to load .obj file " << obj_file);

    std::vector<Vec3f>         vertex_positions;
    std::vector<Vec3f>         texture_coordinates;
    std::vector<Vec3f>         vertex_normals;
    std::vector<FullIndex>     indices;
    unsigned int num_indices = 0u;
    
    constexpr uint32_t RESERVE_AMOUNT = 1024; // 2^11 = 2048
    vertex_positions.reserve(RESERVE_AMOUNT);
    texture_coordinates.reserve(RESERVE_AMOUNT);
    vertex_normals.reserve(RESERVE_AMOUNT);
    indices.reserve(RESERVE_AMOUNT);

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
            s.clear();
            s.str(line);

            switch (line[1])
            {
            case ' ': 
            {
                s >> junk >> temp[0] >> temp[1] >> temp[2];
                vertex_positions.push_back(VEC(temp[0], temp[1], temp[2]));
                break;
            }
            case 'n':
            {
                s >> junk >> junk >> temp[0] >> temp[1] >> temp[2];
                glm::vec3 normal = glm::normalize(glm::vec3(temp[0], temp[1], temp[2]));
                vertex_normals.push_back(VEC(normal.x, normal.y, normal.z));
                break;
            }
            case 't':
            {
                s >> junk >> junk >> temp[0] >> temp[1] >> temp[2];
                texture_coordinates.push_back(VEC(temp[0], temp[1], temp[2]));
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
            FullIndex new_indices[3];
            while (vertex_amount < 3u && *curr != '\n')
            {
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
                        new_indices[vertex_amount] = { 0u, 0u, 0u };
                        new_indices[vertex_amount].position = static_cast<unsigned int>((std::stoul(number)) - 1u);
                        break;
                    case 1u:
                        new_indices[vertex_amount].texture = static_cast<unsigned int>((std::stoul(number)) - 1u);
                        break;
                    case 2u:
                        new_indices[vertex_amount].normal = static_cast<unsigned int>((std::stoul(number)) - 1u);
                        vertex_amount++;
                        num_indices++;
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
            for (auto index : new_indices)
                indices.push_back(index);
        }
    }
    if (vertex_normals.size() < 1)
        vertex_normals.push_back(NULL_VEC);
    if (texture_coordinates.size() < 1)
        texture_coordinates.push_back(NULL_VEC);

    std::vector<Vec3f> vertex_buffer;
    vertex_buffer.reserve(indices.size());
    for (uint32_t i = 0; i < indices.size(); i++)
    {
        vertex_buffer.push_back(vertex_positions[indices[i].position]);
        vertex_buffer.push_back(vertex_normals[indices[i].normal]);
        vertex_buffer.push_back(texture_coordinates[indices[i].texture]);
    }

    *out_count = indices.size();
    out_vbo->set_data((void*)&vertex_buffer[0], vertex_buffer.size() * sizeof(Vec3f));
    GL_CHECK();
    
    //out_ebo->set_data(&index_buffer[0], index_buffer.size());
    //GL_CHECK();

    out_layout->push<float>(3); // position
    out_layout->push<float>(3); // normal
    out_layout->push<float>(3); // texture
}
