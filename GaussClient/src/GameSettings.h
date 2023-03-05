#pragma once
#include "Math/Geometry.h"

inline constexpr int mazeWidth = 4;
inline constexpr int mazeHeight = 3;

inline const GAUSS::Colour blockColour = GAUSS::Colour::White();
inline const GAUSS::Colour breakableBlockColour = GAUSS::Colour(0.2f, 0.5f, 0.7f);
inline constexpr float breakableBlockSpawnChance = 0.2f;
inline constexpr float enemySpawnChance = 0.2f;
inline constexpr float enemySpeed = 40.0f;

inline constexpr float blockSize = 0.8f;
inline constexpr float spacing = 1.3f;
inline constexpr float cameraDistance = -10;

inline constexpr float bombSize = 0.8f;
inline constexpr float timeBetweenBombs = 3.0f;
inline const GAUSS::Colour bombColour = GAUSS::Colour::Red();
