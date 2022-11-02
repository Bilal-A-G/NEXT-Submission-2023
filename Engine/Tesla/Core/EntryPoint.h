#pragma once
#include "../Camera/PerspectiveCamera.h"

inline TESLA::PerspectiveCamera* mainCamera = new TESLA::PerspectiveCamera(90, 0.1, 1000);

extern void Awake();
extern void UpdateLoop(float deltaTime);
extern void CleanUp();

void Init();

void Update(float deltaTime);

void Render();

void Shutdown();