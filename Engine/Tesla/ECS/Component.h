#pragma once
#include "ComponentEnums.h"

namespace TESLA
{
    struct Component
    {
        friend class EntityComponentLookup;
    protected:
        virtual ~Component() = default;
        Component() : m_entityId(0){}
        
        void operator delete(void* ptr){::operator delete(ptr);}
        void* operator new (size_t size){return ::operator new(size);}
    public:
        virtual std::vector<TESLA_ENUMS::ComponentEnum> GetEnum() = 0;
    public:
        int m_entityId;
    };
}
