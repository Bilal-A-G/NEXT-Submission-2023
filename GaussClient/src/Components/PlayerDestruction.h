#pragma once
#include "Destructible.h"
#include "Scenes/SceneManager.h"

namespace CLIENT
{
    class PlayerDestruction final : public CLIENT::Destructible
    {
    public:
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Destructible};}
        void OnDestroy() override
        {
            GAUSS::SceneManager::SwitchScene("GameOver");
        }
    };   
}
