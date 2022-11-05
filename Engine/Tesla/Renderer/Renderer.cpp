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
            mesh->projection = camera->GetProjection();
            mesh->view = camera->GetView();
            
            std::vector<Triangle> projTris = mesh->GetProjectedTriangles();
            
            for (int i = 0; i < projTris.size(); i++)
            {
                App::DrawLine(projTris[i].vertices[0].x, projTris[i].vertices[0].y,
                              projTris[i].vertices[1].x, projTris[i].vertices[1].y);
	
                App::DrawLine(projTris[i].vertices[1].x, projTris[i].vertices[1].y,
                              projTris[i].vertices[2].x, projTris[i].vertices[2].y);

                App::DrawLine(projTris[i].vertices[2].x, projTris[i].vertices[2].y,
                              projTris[i].vertices[0].x, projTris[i].vertices[0].y);
            }
        }
    }
}

