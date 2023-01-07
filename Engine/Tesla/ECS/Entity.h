#pragma once
#include "Component.h"

namespace TESLA
{
    class Entity
    {
    public:
        Entity();
        template<typename T>
        T* GetComponent(TESLA_ENUMS::ComponentEnum enumType)
        {
            TESLA::Component* component = GetComponentFromScene(enumType);
            if(component->GetEnum() != TESLA_ENUMS::Null)
            {
                return static_cast<T*>(component);
            }

            return nullptr;
        }
        template<typename T>
        void AddComponent()
        {
            Component* instantiatedComponent = new T();
            instantiatedComponent->m_entityId = m_id;

            AddComponentToScene(instantiatedComponent);
        }
    private:
        void AddComponentToScene(TESLA::Component* component);
        TESLA::Component* GetComponentFromScene(TESLA_ENUMS::ComponentEnum enumType);
    public:
        uint32_t m_id;
    };
}
