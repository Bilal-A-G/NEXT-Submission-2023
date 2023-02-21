#pragma once
#include "EntityComponentLookup.h"

namespace TESLA
{
    class System
    {
        friend class Scene;
    protected:
        System() = default;
        ~System() = default;
    public:
        virtual void Awake(){return;}
        virtual void Update(float deltaTime, TESLA::EntityComponentLookup& lookup){return;}
        virtual void Render(TESLA::EntityComponentLookup& lookup){return;}
        virtual void Disable(){return;}
    };
   
}