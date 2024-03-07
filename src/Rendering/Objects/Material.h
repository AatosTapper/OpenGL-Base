#pragma once

#include "../../config.h"

#include <string>

class Shader;

struct ShaderInfo
{
    std::string name; // used for hashing in the cache
    std::string vert_path;
    std::string frag_path;
};

struct TextureInfo
{
    std::string path; // this is also used for hashing
};

class BaseMaterial
{
public:
    BaseMaterial();

    virtual Shader *prepare_shader() const = 0;
    void set_albedo(const std::string &path);

protected:
    ShaderInfo m_shader;
    TextureInfo m_albedo;

    void m_prepare_textures() const;
};

class MaterialDefault : public BaseMaterial
{
public:
    MaterialDefault(glm::vec3 _color, float _diffuse, float _speular);
    virtual Shader *prepare_shader() const override;

    glm::vec3 color;
    float diffuse;
    float specular;
};
