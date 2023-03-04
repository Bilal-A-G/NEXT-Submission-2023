#pragma once

namespace GAUSS
{
    struct Entity;
    
    using CollisionFunction = void(*)(Entity& a, Entity& b);
    using CollisionResolvedFunction = void(*)(Entity& a, Entity& b);
}