#include "TSPch.h"
#include "Entity.h"

#include "Scenes/SceneManager.h"

TESLA::Entity::Entity()
{
    TESLA::SceneManager::m_activeScene->CreateEntity(this);
}

TESLA::Component* TESLA::Entity::GetComponentFromScene(TESLA_ENUMS::ComponentEnum enumType)
{
    return TESLA::SceneManager::m_activeScene->GetComponent({enumType}, m_id);
}

TESLA::Component* TESLA::Entity::AddComponentToScene(TESLA::Component* component)
{
    return TESLA::SceneManager::m_activeScene->CreateComponent(component, m_id);
}


