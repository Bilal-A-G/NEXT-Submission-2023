#include "GSPch.h"
#include "ScreenShake.h"

#include "ECS/Components/Camera/Camera.h"
#include "ECS/Components/Transform/Transform.h"

namespace GAUSS
{
    float ScreenShake::m_trauma;
    float ScreenShake::traumaDecreaseRate;

    void ScreenShake::ShakeScreen(float trauma)
    {
        m_trauma += trauma;
    }

    void ScreenShake::Update(float deltaTime, EntityComponentLookup& lookup)
    {
        m_trauma -= deltaTime * traumaDecreaseRate;
        m_trauma = std::clamp(m_trauma, 0.0f, 1.0f);
    
        float amount = rand() / static_cast<float>(RAND_MAX) * m_trauma * m_trauma;
    
        Component* mainCamera = lookup.GetFirstValidComponent<Camera>(GAUSS_ENUMS::Camera);
        Transform* cameraTransform = lookup.GetComponent<Transform>(GAUSS_ENUMS::Transform, mainCamera->m_entityId);
    
        cameraTransform->SetRotation(Vector3(rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX), 0), amount);
    }

    void ScreenShake::Disable()
    {
        m_trauma = 0.0f;
    }
}



