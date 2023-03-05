#include "Explosion.h"

#include "ECS/Entity.h"
#include "ECS/Components/Colliders/BoxCollider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"
#include "Math/Math.h"
#include "../Components/Bomb.h"
#include "../Components/Destructible.h"
#include "ECS/Systems/Particles/Particles.h"

GAUSS::Vector3 explodeDirection;
GAUSS::EntityComponentLookup* globalLookup;

void Explosion::Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup)
{
    globalLookup = &lookup;
    std::vector<GAUSS::Component*> bombComponents = lookup.GetComponents(CLIENT_ENUMS::Bomb);
    std::vector<GAUSS::Component*> transformComponents = lookup.GetComponents(GAUSS_ENUMS::Transform);

    for (int i = 0; i < bombComponents.size(); i++)
    {
        if(!bombComponents[i] || i > transformComponents.size())
            continue;

        CLIENT::Bomb* bomb = static_cast<CLIENT::Bomb*>(bombComponents[i]);
        GAUSS::Transform* transform = static_cast<GAUSS::Transform*>(transformComponents[i]);

        if(!transform || !transform->GetActive() || !bomb->GetActive()) continue;

        if(bomb->fuse > 0)
        {
            bomb->fuse -= bomb->fuseDrainSpeed * deltaTime;
            continue;
        }

         for(int v = 0; v < 4; v++)
         {
             switch (v)
             {
             case 0:
                 explodeDirection = GAUSS::Vector3(0, 1, 0);
                 break;
             case 1:
                 explodeDirection = GAUSS::Vector3(0, -1, 0);
                 break;
             case 2:
                 explodeDirection = GAUSS::Vector3(1, 0, 0);
                 break;
             case 3:
                 explodeDirection = GAUSS::Vector3(-1, 0, 0);
                 break;
             default:
                 break;
             }

             GAUSS::Entity* bombParticle;
             GAUSS::Mesh* mesh;
             GAUSS::Transform* bombTransform;
             GAUSS::BoxCollider* collider;
             GAUSS::Rigidbody* rigidBody;
             
             if(m_bombParticles.size() > v && m_bombParticles[v])
             {
                 bombParticle = m_bombParticles[v];
                 mesh = bombParticle->GetComponent<GAUSS::Mesh>(GAUSS_ENUMS::Mesh);
                 bombTransform = bombParticle->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform);
                 collider = bombParticle->GetComponent<GAUSS::BoxCollider>(GAUSS_ENUMS::BoxCollider);
                 rigidBody = bombParticle->GetComponent<GAUSS::Rigidbody>(GAUSS_ENUMS::RigidBody);
             }
             else
             {
                 bombParticle = lookup.CreateEntity();
                 mesh = bombParticle->AddComponent<GAUSS::Mesh>();
                 bombTransform = bombParticle->AddComponent<GAUSS::Transform>();
                 collider = bombParticle->AddComponent<GAUSS::BoxCollider>();
                 rigidBody = bombParticle->AddComponent<GAUSS::Rigidbody>();
             }
             
             bombParticle->SetActive(true);
             
             mesh->colour = GAUSS::Colour::Red();
             mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
             
             bombTransform->SetScale(GAUSS::Vector3(1, 1, 1), 0.5f);
             bombTransform->SetTranslation(transform->GetPosition());
             
             collider->depth = 10.0f;
             collider->width = 0.8f;
             collider->height = 0.8f;
             collider->stiffness = 0;
             
             collider->OnCollisionStay([](GAUSS::Entity& a, GAUSS::Entity& b)
             {
                 a.SetActive(false);
                 CLIENT::Destructible* destructible = b.GetComponent<CLIENT::Destructible>(CLIENT_ENUMS::Destructible);
                if(destructible)
                {
                    GAUSS::Particles::Play(destructible->explosionParticleProperties, *globalLookup);
                    destructible->OnDestroy();
                    b.SetActive(false);
                }
             });

             rigidBody->hasGravity = false;
             rigidBody->acceleration = explodeDirection * 60.0f;

             m_bombParticles.push_back(bombParticle);
        }
        
        lookup.DestroyEntity(bomb->entityId);
    }
}
