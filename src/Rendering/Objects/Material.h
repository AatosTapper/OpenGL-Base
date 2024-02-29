#pragma once

#include "../../config.h"

#include <string>

class Shader;

// This system is a bit shit due to the abuse of virtual functions but
// it should be fast enough for most stuff.


struct ShaderInfo
{
    std::string name;       // used for hashing in the shader cache
    std::string vert_path;
    std::string frag_path;
};

class Material
{
public:
    // sets the required uniforms and returns the shader for lights, transforms, etc.
    virtual Shader *get_shader() const = 0;

protected:
    ShaderInfo m_shader;
};

class MaterialDefault : public Material
{
public:
    MaterialDefault(glm::vec3 _color, float _diffuse, float _speular);
    virtual Shader *get_shader() const override;

    glm::vec3 color;
    float diffuse;
    float specular;
};
