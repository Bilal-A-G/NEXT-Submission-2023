#pragma once
#include <chrono>
#include "Math/Math.h"

namespace GAUSS
{
    struct Entity;
    class EntityComponentLookup;
}

class BombPlacer final
{
public:
    static void PlaceBomb(GAUSS::EntityComponentLookup* lookup, GAUSS::Vector3 position);
private:
    static bool m_firstTime;
    static std::chrono::time_point<std::chrono::steady_clock> m_lastPlacedBombTime;
    
};
