#pragma once
#include <iostream>

#include "NextAPI/app.h"
#include "Tesla/Scenes/Scene.h"
#include "Tesla/Scenes/SceneManager.h"

class End : public TESLA::Scene
{
public:
    End(std::string name): Scene(name){}

    void Render() override
    {
        App::Print(APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT - 20, "Game Over, press R to restart", 1, 1, 1, GLUT_BITMAP_HELVETICA_10);
    }

    void Update(float deltaTime) override
    {
        if(App::IsKeyPressed('R'))
        {
            TESLA::SceneManager::SwitchScene("MainScene");
        }
    }
};
