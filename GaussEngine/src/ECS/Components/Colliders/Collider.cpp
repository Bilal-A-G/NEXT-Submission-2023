#include "GSPch.h"
#include "Collider.h"

namespace GAUSS
{
    void Collider::InvokeCollision(Entity& other)
    {
        m_resolvedCollision = false;
        for (int i = 0; i < static_cast<int>(m_collisionListeners.size()); i++)
        {
            m_collisionListeners[i](other);
        }
    }

    void Collider::InvokeResolved()
    {
        if(m_resolvedCollision)
            return;

        m_resolvedCollision = true;
        for (int i = 0; i < static_cast<int>(m_resolvedListeners.size()); i++)
        {
            m_resolvedListeners[i]();
        }
    }
    
}
