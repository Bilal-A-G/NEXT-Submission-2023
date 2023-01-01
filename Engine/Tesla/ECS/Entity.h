#pragma once
#include "Component.h"

namespace TESLA
{
    class Entity
    {
    public:
        Entity();
        ComponentBase* GetComponent(ComponentEnum enumType);
        template<typename T> void AddComponent()
        {
            ComponentBase* instantiatedComponent = reinterpret_cast<ComponentBase*>(new T());
            instantiatedComponent->m_entityId = m_id;

            AddComponentToScene(instantiatedComponent);
        }
    private:
        void AddComponentToScene(TESLA::ComponentBase* component);
    public:
        int m_id;
    };
}
