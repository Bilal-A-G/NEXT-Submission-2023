#include <iostream>
#include "../../NextAPI/NextAPI/app.h"
#include "Tesla/Core/EntryPoint.h"
#include "Tesla/Mesh/Mesh.h"
#include "Tesla/Math/Math.h"
#include "Tesla/Mesh/ObjLoader.h"

TESLA::Mesh* mesh;

constexpr float meshSize = 1.0f;

void Awake()
{
	mesh = new TESLA::Mesh(TESLA::ObjLoader::LoadFromOBJFile("Smoothzanne"), TESLA::Vector(1.0f, 0.0f, 0.0f));
	mesh->Scale(meshSize, TESLA::Vector(1,1,1));
	mesh->Translate(TESLA::Vector(0, 0, 1.5));
}

float camSpeed = 0.01f;

void UpdateLoop(float deltaTime)
{
	mesh->Rotate(0.01, TESLA::Vector(0, 1, 0));
	
	if(App::IsKeyPressed('A'))
	{
		mainCamera->position += mainCamera->right * camSpeed;
	}
	if(App::IsKeyPressed('D'))
	{
		mainCamera->position += mainCamera->right * -camSpeed;
	}
	if(App::IsKeyPressed('W'))
	{
		mainCamera->Translate(mainCamera->forward * camSpeed);
	}
	if(App::IsKeyPressed('S'))
	{
		mainCamera->Translate(mainCamera->forward * -camSpeed);
	}
	if(App::IsKeyPressed('Q'))
	{
		mainCamera->Rotate(camSpeed, mainCamera->up);
	}
	if(App::IsKeyPressed('E'))
	{
		mainCamera->Rotate(-camSpeed, mainCamera->up);	
	}
	if(App::IsKeyPressed(VK_CONTROL))
	{
		mainCamera->Translate(mainCamera->up * -camSpeed);
	}
	if(App::IsKeyPressed(VK_SPACE))
	{
		mainCamera->Translate(mainCamera->up * camSpeed);
	}
}

void CleanUp()
{	
	delete(mesh);
}
