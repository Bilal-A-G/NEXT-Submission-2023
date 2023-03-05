#include "KeyboardMovement.h"

#include "API/app.h"
#include "ECS/Entity.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "GameUtils.h"

namespace CLIENT
{
    void KeyboardMovement::Update(GAUSS::EntityComponentLookup& lookup, const float& deltaTime)
    {
        GAUSS::Entity* entity = lookup.GetEntity(entityId);
        if(!entity || !entity->GetActive()) return;

        GAUSS::Rigidbody* rigidBody = entity->GetComponent<GAUSS::Rigidbody>(GAUSS_ENUMS::RigidBody);
        if(!rigidBody || !rigidBody->GetActive()) return;

        GAUSS::Vector3 direction;
        if(App::IsKeyPressed(upKey))
        {
            direction.y = 1;
        }
        if(App::IsKeyPressed(downKey))
        {
            direction.y = -1;
        }
        if(App::IsKeyPressed(leftKey))
        {
            direction.x = -1;
        }
        if(App::IsKeyPressed(rightKey))
        {
            direction.x = 1;
        }

        rigidBody->acceleration += direction.Normalize() * 15 * deltaTime;
        direction = GAUSS::Vector3::Zero();
    }
    
}
