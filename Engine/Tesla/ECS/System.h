#pragma once

namespace TESLA
{
    class System
    {
    public:
        virtual ~System(){}
        virtual void Awake() = 0;
        virtual void Update(){return;}
        virtual void Render(){return;}
        virtual void Disable() = 0;
    };
   
}