#include "GSPch.h"
#include "Scene.h"

namespace GAUSS
{
    void Scene::DisableSystems() const
    {
        m_lookup->CleanUp();
    
        for(System* system : m_systems)
        {
            system->Disable();
        }
    }

    void Scene::UpdateSystems(const float& deltaTime) const
    {
        for (System* system : m_systems)
        {
            system->Update(deltaTime, *m_lookup);
        }
    }

    void Scene::AwakeSystems() const
    {
        for (System* system : m_systems)
        {
            system->Awake();
        }
    }

    void Scene::RenderSystems() const
    {
        for (System* system : m_systems)
        {
            system->Render(*m_lookup);
        }
    }   
}
