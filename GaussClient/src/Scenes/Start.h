#pragma once
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

class Start final : public GAUSS::Scene
{
public:
    Start(const std::string& name) : Scene(name) {}
    
    void Render() override
    {
        App::Print(465, 500, "Bomber Cube", 1, 1, 1, GLUT_BITMAP_HELVETICA_12);
        App::Print(600, 450, "Controls:", 0.8f, 0.8f, 0.8f, GLUT_BITMAP_HELVETICA_10);
        App::Print(610, 410, "WASD - Move", 0.6f, 0.6f, 0.6f, GLUT_BITMAP_HELVETICA_10);
        App::Print(610, 390, "Space - Place Bomb", 0.6f, 0.6f, 0.6f, GLUT_BITMAP_HELVETICA_10);
        App::Print(610, 350, "Destroy all Blue blocks to win!", 0.4f, 0.8f, 0.4f, GLUT_BITMAP_HELVETICA_10);
        App::Print(610, 330, "Don't touch the Red enemies or get blown up!", 0.8f, 0.4f, 0.4f, GLUT_BITMAP_HELVETICA_10);
        App::Print(450, 200, "Press 'P' to play!", 0, 1, 0, GLUT_BITMAP_HELVETICA_12);

    }
    
    void Update(const float& deltaTime) override
    {
        if(App::IsKeyPressed('P'))
            GAUSS::SceneManager::SwitchScene("Game");
    }
};
