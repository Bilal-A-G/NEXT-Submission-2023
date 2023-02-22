#pragma once

namespace GAUSS
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
        Entity* CreateEntity();
        template <typename T>
        T* CreateComponent(int entityId)
        {
            T* component = new T();
            return static_cast<T*>(InitializeNewComponent(entityId, component));
        }
        template <typename T>
        T* GetComponent(int index, int entityId)
        {
            return static_cast<T*>(GetTypelessComponent(index, entityId));
        }
        Entity* GetEntity(int id);
        std::vector<Component*>& GetComponents(int index);
        template <typename T>
        T* GetFirstValidComponent(int index)
        {
            return static_cast<T*>(GetFirstValidTypelessComponent(index));
        }
    private:
        Component* GetTypelessComponent(int index, int entityId);
        Component* GetFirstValidTypelessComponent(int index);
        Component* InitializeNewComponent(int entityId, Component* component);
    private:
        std::vector<Entity*> m_entities;
        std::vector<std::vector<Component*>> m_components;
        int m_lastEntityId;
    };   
}
