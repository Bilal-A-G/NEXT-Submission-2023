#include "TSPch.h"
#include "SceneManager.h"

std::vector<TESLA::Scene*> TESLA::SceneManager::m_scenes;
TESLA::Scene* TESLA::SceneManager::m_activeScene;

void TESLA::SceneManager::SwitchScene(std::string name)
{
    for(Scene* scene : m_scenes)
    {
        if(scene->GetName() == name)
        {
            m_activeScene->Disable();
            m_activeScene->DisableSystems();
            m_activeScene = scene;
            scene->Awake();
            scene->AwakeSystems();
            break;
        }
    }
}

void TESLA::SceneManager::AddScene(TESLA::Scene* scene)
{
    for(Scene* currentScene : m_scenes)
    {
        if(currentScene->GetName() == scene->GetName())
        {
            return;
        }
    }

    m_scenes.push_back(scene);
    if(m_scenes.size() == 1)
    {
        if(m_activeScene == nullptr)
        {
            m_activeScene = m_scenes[0];
        }
    }
}



