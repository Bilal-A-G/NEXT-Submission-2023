#include "GSPch.h"
#include "EntityComponentLookup.h"
#include "Entity.h"
#include "Component.h"

namespace GAUSS
{
    void EntityComponentLookup::CleanUp()
    {
        m_entities.clear();
        m_components.clear();
        m_lastEntityId = 0; 
    }

    EntityComponentLookup::EntityComponentLookup()
    {
        m_entities = std::vector<Entity*>();
        m_components = std::vector<std::vector<Component*>>();
        m_lastEntityId = 0;
    }

    Entity* EntityComponentLookup::CreateEntity()
    {
        m_lastEntityId++;

        Entity* entity = new Entity(m_lastEntityId, *this);
        m_entities.push_back(entity);

        return entity;
    }

    Component* EntityComponentLookup::InitializeNewComponent(int entityId, Component* component)
    {
        std::vector<int> indices = component->GetEnum();
        bool success = false;
    
        for (const int index : indices)
        {
            success = false;
        
            if(m_components.size() <= index + 1)
            {
                m_components.resize(index + 1);
            }

            if(m_components[index].size() <= entityId + 1)
            {
                m_components[index].resize(entityId + 1);
            }
    
            if(m_components[index][entityId])
            {
                continue;
            }

            m_components[index][entityId] = component;
            component->m_entityId = entityId;
            success = true;
        }

        if(!success)
        {
            delete(component);
            return nullptr;
        }
    
        return component;
    }

    Component* EntityComponentLookup::GetTypelessComponent(int index, int entityId)
    {
        if(index >= m_components.size() || entityId >= m_components[index].size() || !m_components[index][entityId])
            return nullptr;
    
        return m_components[index][entityId];
    }

    Entity* EntityComponentLookup::GetEntity(int id)
    {
        if(id - 1 <= m_entities.size())
        {
            return m_entities[id - 1];
        }
    
        return nullptr;
    }

    std::vector<Component*>& EntityComponentLookup::GetComponents(int index)
    {
        if(index < m_components.size())
        {
            return m_components[index];
        }
    
        return m_components[0];
    }

    Component* EntityComponentLookup::GetFirstValidTypelessComponent(int index)
    {
        std::vector<Component*>& components = this->GetComponents(index);
        Component* returnComponent = nullptr;

        for (int i = 0; i < components.size(); i++)
        {
            if(components[i] != nullptr)
            {
                returnComponent = components[i];
                break;
            }
        }

        return returnComponent;
    }
}

