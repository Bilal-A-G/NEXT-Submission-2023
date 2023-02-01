#include "TSPch.h"
#include "ScreenShake.h"
#include "Scenes/SceneManager.h"

TESLA::Transform* TESLA::ScreenShake::m_cameraTransform;
float TESLA::ScreenShake::m_trauma;
float TESLA::ScreenShake::traumaDecreaseRate;

void TESLA::ScreenShake::Awake()
{
    std::vector<TESLA::Component*> cameras = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Camera);
    TESLA::Component* mainCamera;
    
    for(int i = 0; i < cameras.size(); i++)
    {
        if(cameras[i] == nullptr)
            continue;
        
        mainCamera = cameras[i];
        break;
    }

    m_cameraTransform = TESLA::SceneManager::m_activeScene->GetEntity(mainCamera->m_entityId)
    ->GetComponent<TESLA::Transform>(TESLA_ENUMS::Transform);
}

void TESLA::ScreenShake::ShakeScreen(float trauma)
{
    m_trauma += trauma;
}

void TESLA::ScreenShake::Update(float deltaTime)
{
    m_trauma -= deltaTime * traumaDecreaseRate;
    m_trauma = std::clamp(m_trauma, 0.0f, 1.0f);
    
    float amount = rand() / static_cast<float>(RAND_MAX) * m_trauma * m_trauma;
    
    m_cameraTransform->SetRotation(TESLA::Vector(rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX), 0), amount);
}

void TESLA::ScreenShake::Disable()
{
    m_trauma = 0.0f;
}



