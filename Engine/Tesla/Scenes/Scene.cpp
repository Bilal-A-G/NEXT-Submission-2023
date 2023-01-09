#include "tsPch.h"
#include "Scene.h"

void TESLA::Scene::CreateEntity(TESLA::Entity* entity)
{
    m_lastEntityId++;
    
    entity->m_id = m_lastEntityId;
    m_entities.push_back(entity);
}

TESLA::Component* TESLA::Scene::CreateComponent(Component* component, int entityId)
{
    const std::vector<TESLA_ENUMS::ComponentEnum> indices = component->GetEnum();
    bool success = false;
    
    for (const TESLA_ENUMS::ComponentEnum index : indices)
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
        success = true;
    }

    if(!success)
    {
        delete(component);
        return nullptr;
    }
    
    return component;
}

TESLA::Component* TESLA::Scene::GetComponent(std::vector<TESLA_ENUMS::ComponentEnum> indices, int entityId)
{
    for(const TESLA_ENUMS::ComponentEnum index : indices)
    {
        if(index >= m_components.size() || entityId >= m_components[index].size() || !m_components[index][entityId])
            continue;
    
        return m_components[index][entityId];   
    }

    return nullptr;
}


