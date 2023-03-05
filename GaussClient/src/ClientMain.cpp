#include <vector>
#include "API/main.cpp"

#include "ECS/Systems/Particles/Particles.h"
#include "ECS/Systems/Physics/Physics.h"
#include "ECS/Systems/Renderer/Renderer.h"
#include "ECS/Systems/ScreenShake/ScreenShake.h"

#include "ClientECS/Systems/BehaviourUpdater.h"
#include "ClientECS/Systems/Explosion.h"

#include "Scenes/End.h"
#include "Scenes/Game.h"
#include "Scenes/GameOver.h"
#include "Scenes/Start.h"

#include "GameUtils.h"


void SetUp(std::vector<GAUSS::Scene*>& scenes)
{
    GAUSS::Scene* game = new Game(gameSceneName);
    game->RegisterSystem<GAUSS::Physics>();
    game->RegisterSystem<GAUSS::Renderer>();
    game->RegisterSystem<GAUSS::ScreenShake>();
    game->RegisterSystem<GAUSS::Particles>();
    game->RegisterSystem<CLIENT::BehaviourUpdater>();
    game->RegisterSystem<CLIENT::Explosion>();

    GAUSS::Scene* start = new Start(startSceneName);
    GAUSS::Scene* end = new End(endSceneName);
    GAUSS::Scene* gameOver = new GameOver(gameOverSceneName);

    scenes.push_back(start);
    scenes.push_back(game);
    scenes.push_back(gameOver);
    scenes.push_back(end);
}
