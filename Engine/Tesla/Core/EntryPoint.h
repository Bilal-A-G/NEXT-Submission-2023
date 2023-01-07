#pragma once
#include "../Camera/Camera.h"
#include "../Scenes/Scene.h"

inline TESLA::Camera* mainCamera = new TESLA::Camera(70.0f, 0.1f, 1000.0f);

inline std::vector<TESLA::Scene*> scenes;
extern void SetUp(std::vector<TESLA::Scene*>& scenes);

void Init();
void Update(float deltaTime);
void Render();
void Shutdown();