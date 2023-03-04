#include "GSPch.h"
#include "Collider.h"

namespace GAUSS
{
    void Collider::InvokeCollision(Entity* a, Entity* b)
    {
        if(m_collidingWith.size() == 0) {m_collidingWith.push_back(b);}

        bool canAdd = true;
        
        for (int i = 0; i < m_collidingWith.size(); i++)
        {
            if(b->id == m_collidingWith[i]->id)
                canAdd = false;
        }
        
        if(canAdd) {m_collidingWith.push_back(b);}
        
        for (int i = 0; i < static_cast<int>(m_collisionListeners.size()); i++)
        {
            m_collisionListeners[i](*a, *b);
        }
    }

    void Collider::InvokeResolved(Entity* a, Entity* b)
    {
        if(m_collidingWith.size() == 0) return;

        bool erased = false;
        
        for(int i = 0; i < m_collidingWith.size(); i++)
        {
            if(b->id == m_collidingWith[i]->id)
            {
                m_collidingWith.erase(m_collidingWith.begin() + i);
                erased = true;
                break;
            }
        }
        
        if(!erased) return;
        
        for (int i = 0; i < static_cast<int>(m_resolvedListeners.size()); i++)
        {
            m_resolvedListeners[i](*a, *b);
        }
    }
    
}
