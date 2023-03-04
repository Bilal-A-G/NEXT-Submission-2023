#pragma once

namespace GAUSS
{
    struct Entity;
    struct Colour;
    class EntityComponentLookup;
}

class MazeGenerator final
{
public:
    static void GenerateMaze(GAUSS::EntityComponentLookup* lookup);
private:
    static GAUSS::Entity* CreateMazeBlock(GAUSS::EntityComponentLookup* lookup, int widthIndex, int heightIndex);
};
