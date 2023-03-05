#pragma once
#include <vector>

namespace GAUSS
{
    struct Entity;
    struct Vector3;
    class EntityComponentLookup;
}

class BombPlacer final
{
public:
    static void PlaceBomb(GAUSS::EntityComponentLookup* lookup, GAUSS::Vector3 position);
};
