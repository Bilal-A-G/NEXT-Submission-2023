#include "tsPch.h"
#include "Scene.h"

void TESLA::Scene::DisableSystems()
{
    m_lookup->CleanUp();
    
    for(TESLA::System* system : m_systems)
    {
        system->Disable();
    }
}

void TESLA::Scene::UpdateSystems(float deltaTime)
{
    for (TESLA::System* system : m_systems)
    {
        system->Update(deltaTime, *m_lookup);
    }
}

void TESLA::Scene::AwakeSystems()
{
    for (TESLA::System* system : m_systems)
    {
        system->Awake();
    }
}

void TESLA::Scene::RenderSystems()
{
    for (TESLA::System* system : m_systems)
    {
        system->Render(*m_lookup);
    }
}
