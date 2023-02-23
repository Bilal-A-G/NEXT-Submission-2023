#include "GSPch.h"
#include "Renderer.h"

#include <cassert>

#include "API/app.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Camera/Camera.h"
#include "ECS/Components/Transform/Transform.h"
#include "ECS/Components/Light/Light.h"
#include "ECS/ComponentEnums.h"

namespace GAUSS
{
    void Renderer::Render(EntityComponentLookup& lookup)
    {
        const std::vector<Component*>& meshComponents = lookup.GetComponents(GAUSS_ENUMS::Mesh);
        const std::vector<Component*>& transformComponents = lookup.GetComponents(GAUSS_ENUMS::Transform);
    
        const Light* light = lookup.GetFirstValidComponent<Light>(GAUSS_ENUMS::Light);
        const Transform* lightTransform = lookup.GetComponent<Transform>(GAUSS_ENUMS::Transform, light->m_entityId);

        if(!lightTransform)
            assert(false);
    
        const Camera* camera = lookup.GetFirstValidComponent<Camera>(GAUSS_ENUMS::Camera);
        const Transform* cameraTransform = lookup.GetComponent<Transform>(GAUSS_ENUMS::Transform, camera->m_entityId);

        if(!cameraTransform)
            assert(false);
    
        for (Component* component : meshComponents)
        {
            if(component == nullptr) continue;
        
            const Mesh* mesh = static_cast<Mesh*>(component);
            const Transform* transform = static_cast<Transform*>(transformComponents[mesh->m_entityId]);
        
            if(transform == nullptr) continue;
        
            Matrix4x4 model = transform->positionMatrix * transform->rotationMatrix * transform->scaleMatrix;
            std::vector<Face> faces = mesh->faces;
        
            ProjectToWorld(model, faces);
            
            CalculateLighting(faces, lightTransform->position * -1.0f, light->intensity, mesh->colour);

            Matrix4x4 viewMatrix = CalculateView(cameraTransform->position, cameraTransform->forward, cameraTransform->up);
            
            faces = ProjectToView(faces, cameraTransform->position, viewMatrix);
            ProjectToScreen(faces, camera->GetProjection());

            std::vector<Face> nonClippedFaces;

            for (int i = 0; i < 4; i ++)
            {
                for(const Face& face : faces)
                {
                    switch (i)
                    {
                    case 0:
                        ClipAgainstPlane({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, face, nonClippedFaces);
                        continue;
                    case 1:
                        ClipAgainstPlane({0.0f, static_cast<float>(APP_VIRTUAL_HEIGHT) - 1, 0.0f}, {0.0f, -1.0f, 0.0f}, face, nonClippedFaces);
                        continue;
                    case 2:
                        ClipAgainstPlane({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, face, nonClippedFaces);
                        continue;
                    case 3:
                        ClipAgainstPlane({static_cast<float>(APP_VIRTUAL_WIDTH) - 1, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, face, nonClippedFaces);
                        continue;
                    default:
                        continue;
                    }
                }
            }
            
            for (const Face& face : nonClippedFaces)
            {
                std::array<Vector3, 3> currentVertices = face.triangle.vertices;
                const Colour currentColour = face.colour;
                
                App::DrawLine(currentVertices[0].x, currentVertices[0].y,
                              currentVertices[1].x, currentVertices[1].y, currentColour.r, currentColour.g, currentColour.b);
	           
                App::DrawLine(currentVertices[1].x, currentVertices[1].y,
                              currentVertices[2].x, currentVertices[2].y, currentColour.r, currentColour.g, currentColour.b);
            
                App::DrawLine(currentVertices[2].x, currentVertices[2].y,
                              currentVertices[0].x, currentVertices[0].y, currentColour.r, currentColour.g, currentColour.b);
            }
        }
    }
}


