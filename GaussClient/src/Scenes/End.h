#pragma once
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

class End final : public GAUSS::Scene
{
public:
    End(const std::string& name) : Scene(name) {}
    
    void Render() override
    {
        App::Print(100, 100, "Congratulations, you have won the game! Press 'R' to restart", 0, 1, 0, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(const float& deltaTime) override
    {
        if(App::IsKeyPressed('R'))
        {
            GAUSS::SceneManager::SwitchScene("Game");
        }
    }
};
