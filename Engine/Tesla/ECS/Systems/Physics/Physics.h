#pragma once
#include "../../../ECS/Component.h"
#include "../../../ECS/System.h"

namespace TESLA
{
    class Physics : public TESLA::System
    {
    public:
        void Update(float deltaTime) override;
        void Awake() override;
    private:
        bool CheckValidCollider(int colliderIndex);
        bool PerformSAT(std::vector<TESLA::Vector>& verticesA, std::vector<TESLA::Vector>& verticesB, std::vector<TESLA::Vector>& axes,
    TESLA::Vector& resolutionA, TESLA::Vector& resolutionB);
    private:
        std::vector<TESLA::Component*> m_colliders;
        std::vector<TESLA::Component*> m_rigidBodies;
        std::vector<TESLA::Component*> m_transforms;
    public:
        inline static float gravity = -9.8f;
    };   
}
