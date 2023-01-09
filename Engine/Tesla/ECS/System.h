#pragma once

namespace TESLA
{
    class System
    {
    public:
        virtual ~System(){}
        virtual void Awake(){return;}
        virtual void Update(float deltaTime){return;}
        virtual void Render(){return;}
        virtual void Disable(){return;}
    };
   
}