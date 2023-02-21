#pragma once
#include "Scenes/Scene.h"

namespace TESLA
{
    class SceneManager
    {
    public:
        SceneManager() = delete;
        
        static void SwitchScene(std::string name);
        static void AddScene(TESLA::Scene* scene);
    public:
        static Scene* m_activeScene;
        static std::vector<Scene*> m_scenes;
    };
}
