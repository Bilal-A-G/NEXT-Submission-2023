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
            if(component)
            {
                return static_cast<T*>(component);
            }

            return nullptr;
        }
        template<typename T>
        T* AddComponent()
        {
            Component* instantiatedComponent = new T();
            instantiatedComponent->m_entityId = m_id;
            TESLA::Component* createdComponent = AddComponentToScene(instantiatedComponent);
            if(createdComponent)
            {
                return static_cast<T*>(createdComponent);
            }
            else
            {
                return nullptr;
            }
        }
    private:
        TESLA::Component* AddComponentToScene(TESLA::Component* component);
        TESLA::Component* GetComponentFromScene(TESLA_ENUMS::ComponentEnum enumType);
    public:
        uint32_t m_id;
        std::string m_name;
    };
}
