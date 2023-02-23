#include "GSPch.h"
#include "Collider.h"

namespace GAUSS
{
    void Collider::InvokeCollision(Entity& other)
    {
        resolvedCollision = false;
        for (int i = 0; i < static_cast<int>(collisionListeners.size()); i++)
        {
            collisionListeners[i](other);
        }
    }

    void Collider::InvokeResolved()
    {
        if(resolvedCollision)
            return;

        resolvedCollision = true;
        for (int i = 0; i < static_cast<int>(resolvedListeners.size()); i++)
        {
            resolvedListeners[i]();
        }
    }
    
}
