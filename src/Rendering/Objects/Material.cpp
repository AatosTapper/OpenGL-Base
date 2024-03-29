#include "Material.h"

#include "../Shader/Shader.h"
#include "../Objects/Texture.h"
#include "../../util.h"

#include <unordered_map>
#include <memory>

template <typename T>
class Cache
{
public:
    ~Cache()
    {
        for (auto &it : data) delete it.second;
    }

    std::unordered_map<std::string, T*> data;
};

static std::unique_ptr<Cache<Shader>> shader_cache = std::make_unique<Cache<Shader>>();
static std::unique_ptr<Cache<Texture>> texture_cache = std::make_unique<Cache<Texture>>();

static Shader *get_shader_from_cache(const ShaderInfo &shader_info)
{
    if (shader_cache->data.find(shader_info.name) == shader_cache->data.end()) 
    {
        LOG("Created shader \"" << shader_info.name << "\"");
        shader_cache->data[shader_info.name] = new Shader(shader_info.vert_path, shader_info.frag_path);
    }
    return shader_cache->data.at(shader_info.name);
}

static Texture *get_texture_from_cache(const TextureInfo &texture_info)
{
    if (texture_cache->data.find(texture_info.path) == texture_cache->data.end()) 
    {
        LOG("Created shader \"" << texture_info.path << "\"");
        texture_cache->data[texture_info.path] = new Texture(texture_info.path);
    }
    return texture_cache->data.at(texture_info.path);
}

BaseMaterial::BaseMaterial()
    : m_albedo({ .path = "../res/Textures/no_texture.png" }),
      m_ao({ .path = "../res/Textures/no_texture.png" })
{

}

void BaseMaterial::set_albedo(const std::string &path)
{
    m_albedo = {
        .path = path
    };
}

void BaseMaterial::set_ao(const std::string &path)
{
    m_ao = {
        .path = path
    };
}

void BaseMaterial::m_prepare_textures(const Shader *shader) const
{
    shader->use();

    Texture *albedo = get_texture_from_cache(m_albedo);
    glActiveTexture(GL_TEXTURE0);
    albedo->bind();
    shader->set_int("u_albedo_1", 0);

    // TODO: normal here

    /*
    Texture *ao = get_texture_from_cache(m_ao);
    glActiveTexture(GL_TEXTURE1);
    ao->bind();
    shader->set_int("u_ao_1", 1);
    */
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

Shader *MaterialDefault::prepare_shader() const
{
    Shader *shader = get_shader_from_cache(m_shader);
    m_prepare_textures(shader);
    
    shader->set_vec3f("material_color", color);
    shader->set_float("material_diffuse", diffuse);
    shader->set_float("material_specular", specular);

    return shader;
}