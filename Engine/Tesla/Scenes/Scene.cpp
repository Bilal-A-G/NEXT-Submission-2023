#include "tsPch.h"
#include "Scene.h"

void TESLA::Scene::CreateEntity(TESLA::Entity* entity)
{
    m_lastEntityId++;
    
    entity->m_id = m_lastEntityId;
    m_entities.push_back(entity);
}

void TESLA::Scene::CreateComponent(Component* component, int entityId)
{
    const int componentIndex = component->GetEnum();
            
    if(m_components.size() <= componentIndex + 1)
    {
        m_components.resize(componentIndex + 1);
    }

    if(m_components[componentIndex].size() <= entityId + 1)
    {
        m_components[componentIndex].resize(entityId + 1);
    }
    
    if(m_components[componentIndex][entityId])
    {
        delete(component);
        return;
    }
    
    m_components[componentIndex][entityId] = component;
}

TESLA::Component* TESLA::Scene::GetComponent(TESLA_ENUMS::ComponentEnum index, int entityId)
{
    if(index >= m_components.size() || entityId >= m_components[index].size() || !m_components[index][entityId])
        return m_nullComponent;    
    
    return m_components[index][entityId];
}


