#pragma once
#include "string"
#include "../ECS/Component.h"
#include "../ECS/Entity.h"

namespace TESLA
{
    class Scene 
    {
    public:
        virtual ~Scene() = default;
        Scene(std::string name) : m_name(name)
        {
            m_nullComponent = new NullComponent();
            m_lastEntityId = 0;
        }
        
        virtual void Disable(){return;}
        virtual void Update(float deltaTime){return;}
        virtual void Awake(){return;}
        virtual void Render(){return;}
    
        std::string GetName(){return m_name;}
        void CreateEntity(TESLA::Entity* entity);
        void CreateComponent(ComponentBase* component);
        ComponentBase* GetComponent(ComponentEnum index, int entityId);
    private:
        const std::string m_name;
        std::vector<Entity*> m_entities;
        std::vector<std::vector<ComponentBase*>> m_components;
        NullComponent* m_nullComponent;
        int m_lastEntityId;
    };
}
