#pragma once
#include <functional>

namespace GAUSS
{
    struct Entity;
    
    using CollisionFunction = std::function<void (Entity&, Entity&)>;
}