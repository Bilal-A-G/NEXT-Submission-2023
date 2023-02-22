#include "GSPch.h"
#include "SceneManager.h"

namespace GAUSS
{
    std::vector<Scene*> SceneManager::m_scenes;
    Scene* SceneManager::m_activeScene;

    void SceneManager::SwitchScene(std::string name)
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

    void SceneManager::AddScene(Scene* scene)
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
}



