#pragma once
#include "EntityComponentLookup.h"
#include "string"

namespace GAUSS
{
    class EntityComponentLookup;
    
    struct Entity final
    {
        friend class EntityComponentLookup;
    private:
        Entity(const int& id, EntityComponentLookup& lookup) : id(id), m_lookup(lookup), m_active(true) {}
        ~Entity() = default;

        void operator delete(void* ptr){ ::operator delete(ptr);}
        void* operator new (size_t size){ return ::operator new(size);}
    public:
        template <typename T>
        T* AddComponent() {return m_lookup.CreateComponent<T>(id);}

        template <typename T>
        T* GetComponent(const int& index) {return m_lookup.GetComponent<T>(index, id);}

        void SetActive(const bool& active);
        const bool& GetActive() const {return m_active;}
    public:
        const int id;
        std::string name;
    private:
        EntityComponentLookup& m_lookup;
        bool m_active;
    };
}
