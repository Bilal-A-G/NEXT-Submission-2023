#include "GSPch.h"
#include "EntityComponentLookup.h"

#include <cassert>

#include "Entity.h"
#include "Component.h"

namespace GAUSS
{
    void EntityComponentLookup::CleanUp()
    {
        m_entities.clear();
        m_components.clear();
        m_lastEntityId = 0;

        m_components.push_back(std::vector<Component*>());
    }

    Entity* EntityComponentLookup::CreateEntity()
    {
        m_lastEntityId++;

        Entity* entity = new Entity(m_lastEntityId, *this);
        m_entities.push_back(entity);

        return entity;
    }

    void EntityComponentLookup::SetActiveOnComponents(bool active, const int& id)
    {
        for (int i = 1; i < m_components.size(); i++)
        {
            if(m_components[i].size() <= id) continue;
                
            if(m_components[i][id])
            {
                if(i == GAUSS_ENUMS::SphereCollider)
                {
                    m_components[i][id]->m_active = active;
                    continue;
                }
                    
                m_components[i][id]->m_active = active;
                m_components[i][id]->m_active = active;
            }
        }
    }

    Component* EntityComponentLookup::InitializeNewComponent(const int& entityId, Component* component)
    {
        const std::vector<int> indices = component->GetEnum();
        bool success = false;
    
        for (const int index : indices)
        {
            success = false;
        
            if(m_components.size() <= index + 1) {m_components.resize(index + 1);}
            if(m_components[index].size() <= entityId + 1) {m_components[index].resize(entityId + 1);}
            if(m_components[index][entityId]) {continue;}

            m_components[index][entityId] = component;
            component->entityId = entityId;
            success = true;
        }

        if(!success)
        {
            delete(component);
            return nullptr;
        }
    
        return component;
    }

    Component* EntityComponentLookup::GetTypelessComponent(const int& index, const int& entityId) const
    {
        if(index >= m_components.size() || entityId >= m_components[index].size() || !m_components[index][entityId])
            return nullptr;
    
        return m_components[index][entityId];
    }

    Entity* EntityComponentLookup::GetEntity(const int& id) const
    {
        if(id - 1 <= m_entities.size())
        {
            return m_entities[id - 1];
        }
    
        return m_entities[0];
    }

    std::vector<Component*>& EntityComponentLookup::GetComponents(const int& index)
    {
        if(index < m_components.size())
        {
            return m_components[index];
        }
        
        return m_components[0];
    }

    Component* EntityComponentLookup::GetFirstValidTypelessComponent(const int& index)
    {
        const std::vector<Component*>& components = this->GetComponents(index);
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

