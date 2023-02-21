#pragma once

namespace TESLA_ENUMS
{
    enum ComponentEnum : uint8_t;
}

namespace TESLA
{
    struct Entity;
    struct Component;
    
    class EntityComponentLookup
    {
        friend class Scene;
    public:
        ~EntityComponentLookup() = delete;
    private:
        EntityComponentLookup();
        void* operator new(size_t size){return ::operator new(size);}
        void CleanUp();
    public:
        TESLA::Entity* CreateEntity();
        template <typename T>
        T* CreateComponent(int entityId)
        {
            T* component = new T();
            return static_cast<T*>(InitializeNewComponent(entityId, component));
        }
        template <typename T>
        T* GetComponent(TESLA_ENUMS::ComponentEnum index, int entityId)
        {
            return static_cast<T*>(GetTypelessComponent(index, entityId));
        }
        TESLA::Entity* GetEntity(int id);
        std::vector<TESLA::Component*>& GetComponents(TESLA_ENUMS::ComponentEnum index);
        template <typename T>
        T* GetFirstValidComponent(TESLA_ENUMS::ComponentEnum enumType)
        {
            return static_cast<T*>(GetFirstValidTypelessComponent(enumType));
        }
    private:
        TESLA::Component* GetTypelessComponent(TESLA_ENUMS::ComponentEnum index, int entityId);
        TESLA::Component* GetFirstValidTypelessComponent(TESLA_ENUMS::ComponentEnum enumType);
        TESLA::Component* InitializeNewComponent(int entityId, TESLA::Component* component);
    private:
        std::vector<TESLA::Entity*> m_entities;
        std::vector<std::vector<TESLA::Component*>> m_components;
        int m_lastEntityId;
    };   
}
