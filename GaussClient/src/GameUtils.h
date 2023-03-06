#pragma once
#include "Math/Geometry.h"

//Scene Settings
const std::string startSceneName = "Start";
const std::string gameOverSceneName = "GameOver";
const std::string endSceneName = "End";
const std::string gameSceneName = "Game";

const std::string playerTag = "Player";
const std::string enemyTag = "Enemy";
const std::string wallTag = "Wall";
const std::string explosionTag = "Explosion";
const std::string bombTag = "Bomb";

//Player Settings
constexpr float moveSpeed = 20;
constexpr int upKey = 'W';
constexpr int downKey = 'S';
constexpr int leftKey = 'A';
constexpr int rightKey = 'D';

//Camera Settings//
constexpr float cameraCatchUpSpeed = 1;
inline constexpr float cameraDistance = -10;

//Maze Settings//
inline constexpr int mazeWidth = 10;
inline constexpr int mazeHeight = 5;

inline const GAUSS::Colour blockColour = GAUSS::Colour::White();
inline const GAUSS::Colour breakableBlockColour = GAUSS::Colour(0.2f, 0.5f, 0.7f);
inline constexpr float breakableBlockSpawnChance = 0.2f;
inline constexpr float enemySpawnChance = 0.2f;
inline constexpr float enemySpeed = 50.0f;

inline constexpr float blockSize = 0.8f;
inline constexpr float spacing = 1.3f;

//Bomb Settings//
inline constexpr float bombSize = 0.8f;
inline constexpr float timeBetweenBombs = 3.0f;
inline const GAUSS::Colour bombColour = GAUSS::Colour::Red();
inline constexpr float fuse = 10.0f;
inline constexpr float fuseDrainSpeed = 1.0f;
inline constexpr int bombKey = 0x20;

//Util Functions//
#define NEW_SEED rand() / static_cast<float>(RAND_MAX)

inline GAUSS::Vector3 WorldToGridPosition(GAUSS::Vector3 worldPosition)
{
    return GAUSS::Vector3(round(worldPosition.x) * blockSize * spacing, round(worldPosition.y) * blockSize * spacing, -cameraDistance);
}

inline GAUSS::Vector3 GetRandomGridDirection()
{
    float direction = NEW_SEED;
    float sign = NEW_SEED;
    
    if(direction >= 0.5f)
    {
        return GAUSS::Vector3(sign >= 0.5 ? -1 : 1, 0, 0);
    }

    return GAUSS::Vector3(0, sign >= 0.5f ? -1 : 1, 0);
}