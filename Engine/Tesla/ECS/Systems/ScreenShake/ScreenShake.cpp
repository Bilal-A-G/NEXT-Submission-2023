#include "TSPch.h"
#include "ScreenShake.h"

#include "ECS/Components/Camera/Camera.h"
#include "ECS/Components/Transform/Transform.h"

float TESLA::ScreenShake::m_trauma;
float TESLA::ScreenShake::traumaDecreaseRate;

void TESLA::ScreenShake::ShakeScreen(float trauma)
{
    m_trauma += trauma;
}

void TESLA::ScreenShake::Update(float deltaTime, TESLA::EntityComponentLookup& lookup)
{
    m_trauma -= deltaTime * traumaDecreaseRate;
    m_trauma = std::clamp(m_trauma, 0.0f, 1.0f);
    
    float amount = rand() / static_cast<float>(RAND_MAX) * m_trauma * m_trauma;
    
    TESLA::Component* mainCamera = lookup.GetFirstValidComponent<TESLA::Camera>(TESLA_ENUMS::Camera);
    TESLA::Transform* cameraTransform = lookup.GetComponent<TESLA::Transform>(TESLA_ENUMS::Transform, mainCamera->m_entityId);
    
    cameraTransform->SetRotation(TESLA::Vector3(rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX), 0), amount);
}

void TESLA::ScreenShake::Disable()
{
    m_trauma = 0.0f;
}



