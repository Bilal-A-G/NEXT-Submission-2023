#pragma once
#include <vector>

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
    static void CleanUp() {destructibleBlocks.clear();}
private:
    static GAUSS::Entity* CreateMazeBlock(GAUSS::EntityComponentLookup* lookup, int widthIndex, int heightIndex);
public:
    static std::vector<GAUSS::Entity*> destructibleBlocks;
};
