#include "Material.h"

#include "../Shader/Shader.h"
#include "../../util.h"

#include <unordered_map>
#include <memory>

class ShaderCache
{
public:
    ~ShaderCache()
    {
        for (auto &it : data) delete it.second;
    }

    std::unordered_map<std::string, Shader*> data;
};

static std::unique_ptr<ShaderCache> shader_cache = std::make_unique<ShaderCache>();

static Shader *get_shader_from_cache(const ShaderInfo &shader_info)
{
    if (shader_cache->data.find(shader_info.name) == shader_cache->data.end()) 
    {
        LOG("Created shader \"" << shader_info.name << "\"");
        shader_cache->data[shader_info.name] = new Shader(shader_info.vert_path, shader_info.frag_path);
    }
    return shader_cache->data.at(shader_info.name);
}

MaterialDefault::MaterialDefault(glm::vec3 _color, float _diffuse, float _speular)
    : color(_color), diffuse(_diffuse), specular(_speular) 
{
    m_shader = {
        .name = "material_default",
        .vert_path = "../res/Shaders/default.vert",
        .frag_path = "../res/Shaders/default.frag"
    };
}

Shader *MaterialDefault::get_shader() const
{
    Shader *shader = get_shader_from_cache(m_shader);

    shader->use();
    shader->set_vec3f("material_color", color);
    shader->set_float("material_diffuse", diffuse);
    shader->set_float("material_specular", specular);

    return shader;
}