#include "TSPch.h"
#include "Entity.h"

#include "Scenes/SceneManager.h"

TESLA::Entity::Entity()
{
    TESLA::SceneManager::m_activeScene->CreateEntity(this);
}

TESLA::ComponentBase* TESLA::Entity::GetComponent(ComponentEnum enumType)
{
    return TESLA::SceneManager::m_activeScene->GetComponent(enumType, m_id);
}

void TESLA::Entity::AddComponentToScene(TESLA::ComponentBase* component)
{
    TESLA::SceneManager::m_activeScene->CreateComponent(component, m_id);
}


