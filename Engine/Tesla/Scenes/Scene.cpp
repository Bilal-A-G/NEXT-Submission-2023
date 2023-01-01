#include "tsPch.h"
#include "Scene.h"

void TESLA::Scene::CreateEntity(TESLA::Entity* entity)
{
    m_lastEntityId++;
    
    entity->m_id = m_lastEntityId;
    m_entities.push_back(entity);
}

void TESLA::Scene::CreateComponent(ComponentBase* component)
{
    const int componentIndex = component->GetEnum();
            
    if(m_components.size() <= componentIndex + 1)
    {
        m_components.resize(componentIndex + 1);
    }
            
    m_components[componentIndex].push_back(component);
}

TESLA::ComponentBase* TESLA::Scene::GetComponent(ComponentEnum index, int entityId)
{
    
    if(index >= m_components.size())
    {
        return m_nullComponent;    
    }
            
    for (int i = 0; i < m_components[index].size(); i++)
    {
        if(m_components[index][i]->m_entityId == entityId)
        {
            return m_components[index][i];
        }
    }

    return m_nullComponent;
}


