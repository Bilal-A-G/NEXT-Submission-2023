#pragma once
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

class GameOver final : public GAUSS::Scene
{
public:
    GameOver(const std::string& name) : Scene(name) {}
    
    void Render() override
    {
        App::Print(100, 100, "Game Over, Press 'R' to restart", 1, 0, 0, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(const float& deltaTime) override
    {
        if(App::IsKeyPressed('R'))
        {
            GAUSS::SceneManager::SwitchScene("Game");
        }
    }
};
