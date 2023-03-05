#pragma once
#include "Scenes/Scene.h"

class Game final : public GAUSS::Scene
{
public:
    Game(const std::string& name) : Scene(name) {}
    
    void Awake() override;
    void Update(const float& deltaTime) override;
    void Disable() override;
private:
    void InitPlayer();
};
