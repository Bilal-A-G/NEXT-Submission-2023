﻿#pragma once
#include "Scenes/Scene.h"

inline std::vector<GAUSS::Scene*> scenes;
extern void SetUp(std::vector<GAUSS::Scene*>& scenes);

void Init();
void Update(float deltaTime);
void Render();
void Shutdown();