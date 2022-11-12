#pragma once
#include "../Camera/Camera.h"

inline TESLA::Camera* mainCamera = new TESLA::Camera(70.0f, 0.1f, 1000.0f);

extern void Awake();
extern void UpdateLoop(float deltaTime);
extern void CleanUp();

void Init();

void Update(float deltaTime);

void Render();

void Shutdown();