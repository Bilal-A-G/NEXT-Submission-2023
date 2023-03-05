#pragma once
#include "Math/Geometry.h"

constexpr int mazeWidth = 4;
constexpr int mazeHeight = 3;

const GAUSS::Colour blockColour = GAUSS::Colour::White();
const GAUSS::Colour breakableBlockColour = GAUSS::Colour(0.2f, 0.5f, 0.7f);
constexpr float breakableBlockSpawnChance = 0.2f;
constexpr float enemySpawnChance = 0.2f;
constexpr float enemySpeed = 40.0f;

constexpr float blockSize = 0.8f;
constexpr float spacing = 1.3f;
constexpr float cameraDistance = -10;

constexpr float bombSize = 0.8f;
constexpr float timeBetweenBombs = 3.0f;
const GAUSS::Colour bombColour = GAUSS::Colour::Red();
