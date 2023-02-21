#pragma once
#include "string"
#include "ECS/EntityComponentLookup.h"
#include "ECS/System.h"

namespace TESLA
{
    class Scene 
    {
    public:
        Scene(std::string name) : m_name(name), m_systems(std::vector<TESLA::System*>()),
        m_lookup(new TESLA::EntityComponentLookup())
        {}
        virtual ~Scene() = default;
        
        virtual void Disable(){return;}
        void DisableSystems();
        
        virtual void Update(float deltaTime){return;}
        void UpdateSystems(float deltaTime);
        
        virtual void Awake(){return;}
        void AwakeSystems();
        
        virtual void Render(){return;}
        void RenderSystems();

        template <typename T>
        void RegisterSystem()
        {
            T* instantiatedSystem = new T();
            m_systems.push_back(instantiatedSystem);
        }
    
        std::string GetName(){return m_name;}
    protected:
        const std::string m_name;
        std::vector<TESLA::System*> m_systems;
        TESLA::EntityComponentLookup* m_lookup;
    };
}
