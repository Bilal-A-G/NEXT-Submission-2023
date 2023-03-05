#pragma once
#include <vector>

namespace GAUSS
{
    struct Entity;
    struct Component;
    
    class EntityComponentLookup final
    {
        friend class Scene;
    public:
        ~EntityComponentLookup() = delete;
    private:
        EntityComponentLookup() : m_entities(std::vector<Entity*>()), m_components(std::vector<std::vector<Component*>>()), m_lastEntityId(0) {m_components.push_back(std::vector<Component*>());}
        void* operator new(size_t size) {return ::operator new(size);}
        
        void CleanUp();
        Component* GetTypelessComponent(const int& index, const int& entityId) const;
        Component* GetFirstValidTypelessComponent(const int& index);
        Component* InitializeNewComponent(const int& entityId, Component* component);
        void SetActiveOnComponents(const bool& active, const int& id) const;
    public:
        Entity* CreateEntity();
        Entity* GetEntity(const int& id) const;
        
        void DestroyEntity(const int& id) {SetActiveOnComponents(false, id);}
        void ActivateEntity(const int& id) {SetActiveOnComponents(true, id);}
        
        template <typename T>
        T* CreateComponent(const int& entityId) {return static_cast<T*>(InitializeNewComponent(entityId, new T()));}
        
        template <typename T>
        T* GetComponent(const int& index, const int& entityId) {return static_cast<T*>(GetTypelessComponent(index, entityId));}
        
        std::vector<Component*>& GetComponents(const int& index);
        
        template <typename T>
        T* GetFirstValidComponent(const int& index) {return static_cast<T*>(GetFirstValidTypelessComponent(index));}
    private:
        std::vector<Entity*> m_entities;
        std::vector<std::vector<Component*>> m_components;
        int m_lastEntityId;
    };   
}
