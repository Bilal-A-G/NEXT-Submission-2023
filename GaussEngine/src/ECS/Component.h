#pragma once
#include <vector>
#include "ComponentEnums.h"

namespace GAUSS
{
    struct Component
    {
        friend class EntityComponentLookup;
    protected:
        Component() : entityId(0), m_active(true){}
        virtual ~Component() = default;
        
        void operator delete(void* ptr){::operator delete(ptr);}
        void* operator new (size_t size){return ::operator new(size);}
    public:
        virtual std::vector<int> GetEnum() = 0;
        const bool& GetActive() const {return m_active;}
    public:
        int entityId;
    protected:
        bool m_active;
    };
}
