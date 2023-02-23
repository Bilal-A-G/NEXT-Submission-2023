#pragma once
#include "ECS/System.h"

namespace GAUSS
{
    class Renderer final : public System
    {
        friend class Scene;
    protected:
        Renderer() = default;
        ~Renderer() override = default;
    public:
        void Render(EntityComponentLookup& lookup) override;
    };   
}
