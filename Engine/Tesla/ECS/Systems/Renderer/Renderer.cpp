#include "TSPch.h"
#include "Renderer.h"

#include <cassert>

#include "App/app.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Camera/Camera.h"
#include "ECS/Components/Transform/Transform.h"
#include "ECS/Components/Light/Light.h"

void TESLA::Renderer::Render(TESLA::EntityComponentLookup& lookup)
{
    std::vector<TESLA::Component*>& meshComponents = lookup.GetComponents(TESLA_ENUMS::Mesh);
    std::vector<TESLA::Component*>& transformComponents = lookup.GetComponents(TESLA_ENUMS::Transform);
    
    TESLA::Light* light = lookup.GetFirstValidComponent<TESLA::Light>(TESLA_ENUMS::Light);
    TESLA::Transform* lightTransform = lookup.GetComponent<TESLA::Transform>(TESLA_ENUMS::Transform, light->m_entityId);

    if(!lightTransform)
        assert(false);
    
    TESLA::Camera* camera = lookup.GetFirstValidComponent<TESLA::Camera>(TESLA_ENUMS::Camera);
    TESLA::Transform* cameraTransform = lookup.GetComponent<Transform>(TESLA_ENUMS::Transform, camera->m_entityId);

    if(!cameraTransform)
        assert(false);
    
    for (TESLA::Component* component : meshComponents)
    {
        if(component == nullptr)
            continue;
        
        Mesh* mesh = static_cast<Mesh*>(component);
        Transform* transform = static_cast<Transform*>(transformComponents[mesh->m_entityId]);
        
        if(transform == nullptr)
            continue;
        
        Matrix4x4 model = transform->positionMatrix * transform->rotationMatrix * transform->scaleMatrix;
        std::vector<Face> faces = TESLA::ProjectToWorld(model, mesh->faces);
        
        TESLA::CalculateLighting(faces, lightTransform->position * -1.0f, light->intensity, mesh->colour);
        
        faces = TESLA::ProjectToView(faces, cameraTransform->position,
            CalculateView(cameraTransform->position, cameraTransform->forward, cameraTransform->up));
        faces = TESLA::ProjectToScreen(faces, camera->GetProjection());

        std::vector<Face> nonClippedFaces;

        //Clipping against screen edges!
        for (int i = 0; i < 4; i ++)
        {
            for(Face face : faces)
            {
                switch (i)
                {
                case 0:
                    ClipAgainstPlane({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, face, nonClippedFaces);
                    continue;
                case 1:
                    ClipAgainstPlane({0.0f, float(APP_VIRTUAL_HEIGHT) - 1, 0.0f}, {0.0f, -1.0f, 0.0f}, face, nonClippedFaces);
                    continue;
                case 2:
                    ClipAgainstPlane({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, face, nonClippedFaces);
                    continue;
                case 3:
                    ClipAgainstPlane({float(APP_VIRTUAL_WIDTH) - 1, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, face, nonClippedFaces);
                    continue;
                default:
                    continue;
                }
            }
        }
            
        for (Face face : nonClippedFaces)
        {
            std::array<Vector, 3> currentVertices = face.triangle.vertices;
            Colour currentColour = face.colour;
                
            App::DrawLine(currentVertices[0].x, currentVertices[0].y,
                          currentVertices[1].x, currentVertices[1].y, currentColour.r, currentColour.g, currentColour.b);
	           
            App::DrawLine(currentVertices[1].x, currentVertices[1].y,
                          currentVertices[2].x, currentVertices[2].y, currentColour.r, currentColour.g, currentColour.b);
            
            App::DrawLine(currentVertices[2].x, currentVertices[2].y,
                          currentVertices[0].x, currentVertices[0].y, currentColour.r, currentColour.g, currentColour.b);
        }
    }
}


