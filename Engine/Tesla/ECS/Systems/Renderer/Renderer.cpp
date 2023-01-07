#include "TSPch.h"
#include "Renderer.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "NextAPI/app.h"
#include "Scenes/SceneManager.h"

void TESLA::Renderer::Awake()
{
    m_components = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Mesh);
}

void TESLA::Renderer::Disable()
{
    m_components.clear();
}

void TESLA::Renderer::Render()
{
    for (TESLA::Component* component : m_components)
    {
        if(component == nullptr || component->GetEnum() == TESLA_ENUMS::Null)
            continue;
        
        Mesh* mesh = static_cast<Mesh*>(component);
        
        Matrix4x4 model = mesh->m_translationMatrix * mesh->m_rotationMatrix * mesh->m_scaleMatrix;
        std::vector<Face> faces = TESLA::ProjectToWorld(model, mesh->faces);
        
        TESLA::CalculateLighting(faces, TESLA::Vector(50, -50, 0), 0.8, mesh->colour);

        faces = TESLA::ProjectToView(faces, m_camera->position, m_camera->GetView());
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

