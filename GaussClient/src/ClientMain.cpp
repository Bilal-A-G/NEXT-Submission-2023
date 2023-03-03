#include <vector>
#include "API/main.cpp"

#include "ECS/Systems/Particles/Particles.h"
#include "ECS/Systems/Physics/Physics.h"
#include "ECS/Systems/Renderer/Renderer.h"
#include "ECS/Systems/ScreenShake/ScreenShake.h"

#include "Scenes/End.h"
#include "Scenes/Game.h"
#include "Scenes/GameOver.h"
#include "Scenes/Start.h"


void SetUp(std::vector<GAUSS::Scene*>& scenes)
{
    GAUSS::Scene* game = new Game("Game");
    game->RegisterSystem<GAUSS::Physics>();
    game->RegisterSystem<GAUSS::Renderer>();
    game->RegisterSystem<GAUSS::ScreenShake>();
    game->RegisterSystem<GAUSS::Particles>();

    GAUSS::Scene* start = new Start("Start");
    GAUSS::Scene* end = new End("End");
    GAUSS::Scene* gameOver = new GameOver("GameOver");

    scenes.push_back(start);
    scenes.push_back(game);
    scenes.push_back(gameOver);
    scenes.push_back(end);
}
