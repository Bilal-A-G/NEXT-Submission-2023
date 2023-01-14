#include <vector>

#include "Scenes/MeshTest.h"
#include "Scenes/End.h"
#include "Tesla/Core/EntryPoint.h"
#include "Tesla/ECS/Systems/Physics/Physics.h"
#include "Tesla/ECS/Systems/Renderer/Renderer.h"

void SetUp(std::vector<TESLA::Scene*>& scenes)
{
    TESLA::Scene* meshTestScene = new MeshTest("MainScene");
    meshTestScene->RegisterSystem(new TESLA::Renderer());
    meshTestScene->RegisterSystem(new TESLA::Physics());
    
    TESLA::Scene* endScene = new End("EndScene");

    scenes.push_back(meshTestScene);
    scenes.push_back(endScene);
}
