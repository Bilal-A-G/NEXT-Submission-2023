#include <vector>

#include "Scenes/MeshTest.h"
#include "Scenes/End.h"
#include "Tesla/Core/EntryPoint.h"

std::vector<TESLA::Scene*> scenes
{
    new MeshTest(mainCamera, "MainScene"),
    new End("EndScene"),
};
