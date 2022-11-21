#pragma once
#include "string"

namespace TESLA
{
    class Scene 
    {
    public:
        virtual ~Scene() = default;
        Scene(std::string name) : m_name(name){}
        
        virtual void Disable(){return;}
        virtual void Update(float deltaTime){return;}
        virtual void Awake(){return;}
        virtual void Render(){return;}
    
        std::string GetName(){return m_name;}
    public:
        std::string m_name;
    };
}
