#pragma once

namespace GAUSS
{
    struct Colour;
    class EntityComponentLookup;
}

class MazeGenerator final
{
public:
    static void GenerateMaze(GAUSS::EntityComponentLookup* lookup);
};
