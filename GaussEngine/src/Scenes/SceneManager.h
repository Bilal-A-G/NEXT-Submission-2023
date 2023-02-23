#pragma once
#include "Scenes/Scene.h"

namespace GAUSS
{
    class SceneManager final
    {
    public:
        SceneManager() = delete;
        ~SceneManager() = delete;
        
        static void SwitchScene(const std::string& name);
        static void AddScene(Scene* scene);
    public:
        static Scene* m_activeScene;
        static std::vector<Scene*> m_scenes;
    };
}
