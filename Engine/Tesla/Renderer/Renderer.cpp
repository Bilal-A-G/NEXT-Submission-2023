#include "TSPch.h"
#include "Renderer/Renderer.h"

#include "Mesh/Mesh.h"
#include "NextAPI/app.h"

void TESLA::Renderer::Update(TESLA::PerspectiveCamera* camera)
{
    for (auto element : RenderQueue::GetQueue())
    {
        if(auto mesh = static_cast<Mesh*>(element))
        {
            mesh->projection = camera->GetProjection();
            mesh->view = camera->GetView();
            
            for (Triangle triangle : mesh->GetProjectedTriangles())
            {
                App::DrawLine(triangle.vertices[0].x, triangle.vertices[0].y,
                    triangle.vertices[1].x, triangle.vertices[1].y);
	
                App::DrawLine(triangle.vertices[1].x, triangle.vertices[1].y,
                    triangle.vertices[2].x, triangle.vertices[2].y);
            }
        }
    }
}

