#include "TSPch.h"
#include "Renderer/Renderer.h"

#include "Mesh/Mesh.h"
#include "NextAPI/app.h"

void TESLA::Renderer::Update(TESLA::Camera* camera)
{
    for (auto element : RenderQueue::GetQueue())
    {
        if(auto mesh = static_cast<Mesh*>(element))
        {
            std::vector<Face> faces = mesh->GetProjectedFaces(camera->GetView(), camera->GetProjection());
            mesh->RecalculateLighting(faces, TESLA::Vector(0, 9, 0), 0.8);
            
            for (Face face : faces)
            {
                std::array<Vector, 3> currentVertices = face.triangle.vertices;
                Vector currentColour = face.colour;
                
                App::DrawLine(currentVertices[0].x, currentVertices[0].y,
                              currentVertices[1].x, currentVertices[1].y, currentColour.x, currentColour.y, currentColour.z);
	
                App::DrawLine(currentVertices[1].x, currentVertices[1].y,
                              currentVertices[2].x, currentVertices[2].y, currentColour.x, currentColour.y, currentColour.z);

                App::DrawLine(currentVertices[2].x, currentVertices[2].y,
                              currentVertices[0].x, currentVertices[0].y, currentColour.x, currentColour.y, currentColour.z);
            }
        }
    }
}

