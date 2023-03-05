#include "GSPch.h"
#include "Entity.h"

namespace GAUSS
{
    void Entity::SetActive(bool active)
    {
        if(!active)
        {
            m_lookup.DestroyEntity(id);
        }
        else
        {
            m_lookup.ActivateEntity(id);
        }
        m_active = active;
    }
    
}
