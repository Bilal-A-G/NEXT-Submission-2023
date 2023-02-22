#include "GSPch.h"
#include "Scene.h"

namespace GAUSS
{
    void Scene::DisableSystems()
    {
        m_lookup->CleanUp();
    
        for(System* system : m_systems)
        {
            system->Disable();
        }
    }

    void Scene::UpdateSystems(float deltaTime)
    {
        for (System* system : m_systems)
        {
            system->Update(deltaTime, *m_lookup);
        }
    }

    void Scene::AwakeSystems()
    {
        for (System* system : m_systems)
        {
            system->Awake();
        }
    }

    void Scene::RenderSystems()
    {
        for (System* system : m_systems)
        {
            system->Render(*m_lookup);
        }
    }   
}
