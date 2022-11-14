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

