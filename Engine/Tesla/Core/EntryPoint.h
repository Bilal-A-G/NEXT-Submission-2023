#pragma once
#include "../Camera/Camera.h"

inline TESLA::Camera* mainCamera = new TESLA::Camera(100, 0.1, 1000);

extern void Awake();
extern void UpdateLoop(float deltaTime);
extern void CleanUp();

void Init();

void Update(float deltaTime);

void Render();

void Shutdown();