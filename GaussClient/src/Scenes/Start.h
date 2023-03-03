#pragma once
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

class Start final : public GAUSS::Scene
{
public:
    Start(const std::string& name) : Scene(name) {}
    
    void Render() override
    {
        App::Print(50, 500, "Welcome to the Game, Press 'Space' to play", 1, 1, 1, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(const float& deltaTime) override
    {
        if(App::IsKeyPressed(VK_SPACE))
            GAUSS::SceneManager::SwitchScene("Game");
    }
};
