#pragma once
#include "EntityComponentLookup.h"

namespace GAUSS
{
    class System
    {
        friend class Scene;
    protected:
        System() = default;
        ~System() = default;
    public:
        virtual void Awake(){return;}
        virtual void Update(float deltaTime, EntityComponentLookup& lookup){return;}
        virtual void Render(EntityComponentLookup& lookup){return;}
        virtual void Disable(){return;}
    };
   
}