#pragma once

#include "../util.h"
#include "Entity.h"

#include <stdbool.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <any>
#include <typeindex>
#include <memory>

// This makes it possible to store pointers in the component manager
template <typename T> 
struct ECPointer 
{
    ECPointer(T *_ptr) : ptr(_ptr) 
    {
        ASSERT(_ptr, "ECPointer can't be initialized with a nullptr");
    }
    
    T *ptr;

    void destroy()
    {
        if (ptr != nullptr) 
        {
            delete ptr;
            ptr = nullptr;
        }
    }
};

class BaseComponent 
{
public:
    virtual ~BaseComponent() = default;
};

template <typename T>
class ComponentArray : public BaseComponent 
{
public:
    std::vector<T> data;
};

class ECManager
{
public:
    ECManager() : m_last_entity_index(0) {}

    Entity add_entity(ENT_TYPE type = ENT_TYPE::DEFAULT)
    {
        const Entity new_entity = Entity{ m_last_entity_index++, type };
        m_entities.push_back(new_entity);
        return new_entity;
    }

    template <typename T>
    void add_component(const Entity &entity, T component) 
    {
        const size_t component_type_hash = typeid(T).hash_code();
        if (m_components.find(component_type_hash) == m_components.end()) 
        {
            m_components[component_type_hash] = std::make_unique<ComponentArray<T>>();
        }
        auto& component_array = dynamic_cast<ComponentArray<T>&>(*m_components[component_type_hash]).data;
        component_array.push_back(component);
        m_entity_indices[entity.id][component_type_hash] = component_array.size() - 1;
    }

    template <typename T>
    void add_component(const Entity &entity, ECPointer<T> ecPointer) 
    {
        const size_t component_type_hash = typeid(ECPointer<T>).hash_code();
        if (m_components.find(component_type_hash) == m_components.end()) 
        {
            m_components[component_type_hash] = std::make_unique<ComponentArray<ECPointer<T>>>();
        }
        auto& component_array = dynamic_cast<ComponentArray<ECPointer<T>>&>(*m_components[component_type_hash]).data;
        component_array.push_back(ecPointer);
        m_entity_indices[entity.id][component_type_hash] = component_array.size() - 1;
    }

    template <typename T>
    bool has_component(const Entity &entity)
    {
        const size_t component_type_hash = typeid(T).hash_code();
        if (m_entity_indices.find(entity.id) == m_entity_indices.end()
            || m_entity_indices[entity.id].find(component_type_hash) == m_entity_indices[entity.id].end()) 
        {
            return false;
        }
        return true;
    }

    std::vector<Entity> *get_all_entities()
    {
        return &m_entities;
    }

    template <typename T>
    int64_t get_component_index(const Entity &entity, bool silence_warnings = false)
    {
        ASSERT(entity.id != ENT_TYPE::COMP_GROUP, "Can't access single components for an entity with type of component group");
        const size_t component_type_hash = typeid(T).hash_code();
        auto entity_iter = m_entity_indices.find(entity.id);
        if (entity_iter != m_entity_indices.end()) 
        {
            auto component_iter = entity_iter->second.find(component_type_hash);
            if (component_iter != entity_iter->second.end()) 
            {
                return component_iter->second;
            }
        }
        if (!silence_warnings)
            WARN("Component of type [ " << typeid(T).name() << " ] doesn't exist for entity [ " << entity.id << " ]");
        return -1;
    }

    template <typename T>
    T *get_component(const Entity &entity, bool silence_warnings = false) 
    {
        ASSERT(entity.id != ENT_TYPE::COMP_GROUP, "Can't access single components for an entity with type of component group");
        const size_t component_type_hash = typeid(T).hash_code();
        if (m_entity_indices.find(entity.id) == m_entity_indices.end() 
            || m_entity_indices[entity.id].find(component_type_hash) == m_entity_indices[entity.id].end()) 
        {
            if (!silence_warnings)
                WARN("Component of type [ " << typeid(T).name() << " ] doesn't exist for entity [ " << entity.id << " ]");
            return nullptr;
        }
        size_t index = m_entity_indices[entity.id][component_type_hash];
        return &dynamic_cast<ComponentArray<T>&>(*m_components[component_type_hash]).data[index];
    }

    // Creates a vector for the component if it isn't found
    template <typename T>
    std::vector<T> *get_all_components() 
    {
        const size_t component_type_hash = typeid(T).hash_code();
        if (m_components.find(component_type_hash) == m_components.end()) 
        {
            m_components[component_type_hash] = std::make_unique<ComponentArray<T>>();
        }
        return &dynamic_cast<ComponentArray<T>&>(*m_components.at(component_type_hash)).data;
    }

    void remove_entity(Entity entity) 
    {
        bool has_components = false;
        if (m_entity_indices.find(entity.id) != m_entity_indices.end()) 
        {
            for (const auto& entry : m_entity_indices[entity.id]) 
            {
                has_components = true;
                static_cast<void>(entry);
                break;
            }
            m_entity_indices.erase(entity.id);
        }

        int64_t deleted_entity_index = -1;
        for (int64_t i = 0; i < m_entities.size(); i++)
        {
            if (m_entities[i].id == entity.id)
            {
                deleted_entity_index = i;
                break;
            }
        }
        if (deleted_entity_index == -1)
        {
            WARN("Tried to delete an entity that doesn't exist.");
            return;
        }
        m_entities.erase(m_entities.begin() + deleted_entity_index);

        if (has_components)
            ERR("Removing entity doesn't automatically remove it's components. \n  Existing components detected for entity [ " << entity.id << " ]");
    }

    template <typename T>
    void remove_component(Entity entity) 
    {
        const size_t component_type_hash = typeid(T).hash_code();

        if (m_entity_indices.find(entity.id) != m_entity_indices.end() &&
            m_entity_indices[entity.id].find(component_type_hash) != m_entity_indices[entity.id].end()) 
        {
            const size_t index = m_entity_indices[entity.id][component_type_hash];

            auto& component_array = dynamic_cast<ComponentArray<T>&>(*m_components[component_type_hash]).data;
            component_array.erase(component_array.begin() + index);

            m_entity_indices[entity.id].erase(component_type_hash);

            if (component_array.empty()) 
            {
                m_components.erase(component_type_hash);
            }
        }
        else
        {
            WARN("Tried to delete a component that doesn't exist.");
        }
    }

private:
    std::unordered_map<size_t, std::unique_ptr<BaseComponent>> m_components;
    std::unordered_map<uint32_t, std::unordered_map<size_t, size_t>> m_entity_indices;
    std::vector<Entity> m_entities;
    uint32_t m_last_entity_index;
};
