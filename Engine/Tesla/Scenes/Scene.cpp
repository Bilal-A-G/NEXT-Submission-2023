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
    
    for (int i = 0; i < m_components[componentIndex].size(); i++)
    {
        if(m_components[componentIndex][i]->m_entityId == entityId)
        {
            delete(component);
            return;
        }
    }
    
    m_components[componentIndex].push_back(component);
}

TESLA::Component* TESLA::Scene::GetComponent(TESLA_ENUMS::ComponentEnum index, int entityId)
{
    if(index >= m_components.size())
        return m_nullComponent;    

    for (Component* component : m_components[index])
    {
        if(component->m_entityId == entityId)
        {
            return component;
        }
    }
    
    return m_nullComponent;
}


