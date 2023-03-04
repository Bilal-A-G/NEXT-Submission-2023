#pragma once
#include <vector>
#include "ComponentEnums.h"

namespace GAUSS
{
    struct Component
    {
        friend class EntityComponentLookup;
    protected:
        Component() : entityId(0){}
        virtual ~Component() = default;
        
        void operator delete(void* ptr){::operator delete(ptr);}
        void* operator new (size_t size){return ::operator new(size);}
    public:
        virtual std::vector<int> GetEnum() = 0;
    public:
        int entityId;
        bool active;
    };
}
