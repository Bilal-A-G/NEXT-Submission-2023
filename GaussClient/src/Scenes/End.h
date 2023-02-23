#pragma once
#include <iostream>

#include "API/app.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

class End : public GAUSS::Scene
{
public:
    End(std::string name): Scene(name){}

    void Render() override
    {
        App::Print(APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT - 20, "Game Over, press R to restart", 1, 1, 1, GLUT_BITMAP_HELVETICA_10);
    }

    void Update(const float& deltaTime) override
    {
        if(App::IsKeyPressed('R'))
        {
            GAUSS::SceneManager::SwitchScene("MainScene");
        }
    }
};
