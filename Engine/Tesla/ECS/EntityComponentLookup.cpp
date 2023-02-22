#include "TSPch.h"
#include "EntityComponentLookup.h"
#include "Entity.h"
#include "Component.h"

void TESLA::EntityComponentLookup::CleanUp()
{
    m_entities.clear();
    m_components.clear();
    m_lastEntityId = 0; 
}

TESLA::EntityComponentLookup::EntityComponentLookup()
{
    m_entities = std::vector<TESLA::Entity*>();
    m_components = std::vector<std::vector<TESLA::Component*>>();
    m_lastEntityId = 0;
}

TESLA::Entity* TESLA::EntityComponentLookup::CreateEntity()
{
    m_lastEntityId++;

    TESLA::Entity* entity = new Entity(m_lastEntityId, *this);
    m_entities.push_back(entity);

    return entity;
}

TESLA::Component* TESLA::EntityComponentLookup::InitializeNewComponent(int entityId, TESLA::Component* component)
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

TESLA::Component* TESLA::EntityComponentLookup::GetTypelessComponent(int index, int entityId)
{
    if(index >= m_components.size() || entityId >= m_components[index].size() || !m_components[index][entityId])
        return nullptr;
    
    return m_components[index][entityId];
}

TESLA::Entity* TESLA::EntityComponentLookup::GetEntity(int id)
{
    if(id - 1 <= m_entities.size())
    {
        return m_entities[id - 1];
    }
    
    return nullptr;
}

std::vector<TESLA::Component*>& TESLA::EntityComponentLookup::GetComponents(int index)
{
    if(index < m_components.size())
    {
        return m_components[index];
    }
    
    return m_components[0];
}

TESLA::Component* TESLA::EntityComponentLookup::GetFirstValidTypelessComponent(int index)
{
    std::vector<TESLA::Component*>& components = this->GetComponents(index);
    TESLA::Component* returnComponent = nullptr;

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

