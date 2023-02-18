#include "TSPch.h"
#include "Renderer.h"

#include <cassert>

#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Transform/Transform.h"
#include "App/app.h"
#include "Scenes/SceneManager.h"

void TESLA::Renderer::Awake()
{
    m_meshComponents = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Mesh);
    m_transformComponents = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Transform);
    std::vector<TESLA::Component*> lights = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Light);

    for (int i = 0; i < lights.size(); i++)
    {
        if(lights[i] != nullptr)
        {
            m_light = static_cast<TESLA::Light*>(lights[i]);
            break;
        }
    }

    if(m_light == nullptr)
        assert(false);

    m_lightTransform = TESLA::SceneManager::m_activeScene->GetEntity(m_light->m_entityId)->GetComponent<TESLA::Transform>(TESLA_ENUMS::Transform);
    
    std::vector<TESLA::Component*> cameras = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Camera);

    for (int i = 0; i < cameras.size(); i++)
    {
        if(cameras[i] != nullptr)
        {
            m_camera = static_cast<TESLA::Camera*>(cameras[i]);
            break;
        }
    }

    if(m_camera == nullptr)
        assert(false);

    m_cameraTransform = TESLA::SceneManager::m_activeScene->GetEntity(m_camera->m_entityId)->GetComponent<TESLA::Transform>(TESLA_ENUMS::Transform);
}

void TESLA::Renderer::Render()
{
    if(!m_camera)
        return;
    
    for (TESLA::Component* component : m_meshComponents)
    {
        if(component == nullptr)
            continue;
        
        Mesh* mesh = static_cast<Mesh*>(component);
        Transform* transform = static_cast<Transform*>(m_transformComponents[mesh->m_entityId]);
        
        if(transform == nullptr)
            continue;
        
        Matrix4x4 model = transform->positionMatrix * transform->rotationMatrix * transform->scaleMatrix;
        std::vector<Face> faces = TESLA::ProjectToWorld(model, mesh->faces);
        
        TESLA::CalculateLighting(faces, m_lightTransform->position * -1.0f, m_light->intensity, mesh->colour);
        
        faces = TESLA::ProjectToView(faces, m_cameraTransform->position,
            CalculateView(m_cameraTransform->position, m_cameraTransform->forward, m_cameraTransform->up));
        faces = TESLA::ProjectToScreen(faces, m_camera->GetProjection());

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

