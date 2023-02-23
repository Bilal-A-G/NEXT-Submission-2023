#pragma once
#include "string"
#include "ECS/EntityComponentLookup.h"
#include "ECS/System.h"

namespace GAUSS
{
    class Scene 
    {
    public:
        Scene(const std::string& name) : m_name(name), m_systems(std::vector<System*>()),m_lookup(new EntityComponentLookup()){}
        virtual ~Scene() = default;
        
        virtual void Disable() {return;}
        void DisableSystems() const;
        
        virtual void Update(const float& deltaTime) {return;}
        void UpdateSystems(const float& deltaTime) const;
        
        virtual void Awake() {return;}
        void AwakeSystems() const;
        
        virtual void Render() {return;}
        void RenderSystems() const;

        template <typename T>
        void RegisterSystem() {m_systems.push_back(new T());}
    
        const std::string& GetName() const {return m_name;}
    protected:
        const std::string m_name;
        std::vector<System*> m_systems;
        EntityComponentLookup* m_lookup;
    };
}
