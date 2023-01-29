#pragma once
#include "../Scenes/Scene.h"

namespace TESLA
{
    class SceneManager
    {
    public:
        SceneManager() = delete;
        
        static void SwitchScene(std::string name);
        static void AddScene(TESLA::Scene* scene);
        
        static void Init(){m_activeScene->Awake();}
        static void InitSystems(){m_activeScene->AwakeSystems();}
        static void Update(float deltaTime){m_activeScene->Update(deltaTime);}
        static void UpdateSystems(float deltaTime){m_activeScene->UpdateSystems(deltaTime);}
        static void Render(){m_activeScene->Render();}
        static void RenderSystems(){m_activeScene->RenderSystems();}
        static void Disable(){m_activeScene->Disable();}
        static void DisableSystems(){m_activeScene->DisableSystems();}
    public:
        static Scene* m_activeScene;
        static std::vector<Scene*> m_scenes;
    };
}
