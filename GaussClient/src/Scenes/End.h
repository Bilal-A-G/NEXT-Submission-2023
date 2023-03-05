#pragma once
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

class End final : public GAUSS::Scene
{
public:
    End(const std::string& name) : Scene(name) {}
    
    void Render() override
    {
        App::Print(380, 500, "Congratulations, you have won Bomber Cube!", 0.4f, 0.8f, 0.4f, GLUT_BITMAP_HELVETICA_12);
        App::Print(550, 460, "Press 'R' to restart", 0.8f, 0.8f, 0.8f, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(const float& deltaTime) override
    {
        if(App::IsKeyPressed('R'))
        {
            GAUSS::SceneManager::SwitchScene("Game");
        }
    }
};
