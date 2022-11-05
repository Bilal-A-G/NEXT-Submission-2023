#include <iostream>
#include "../../NextAPI/NextAPI/app.h"
#include "Tesla/Core/EntryPoint.h"
#include "Tesla/Mesh/Mesh.h"
#include "Tesla/Math/Math.h"
#include "Tesla/Mesh/ObjLoader.h"

TESLA::Mesh* suzanne;

constexpr float cubeSize = 2.0f;
bool debounce;

void Awake()
{
	suzanne = new TESLA::Mesh(TESLA::ObjLoader::LoadFromOBJFile("Suzanne"));
	suzanne->Scale(cubeSize, TESLA::Vector(1,1,1));
	suzanne->Translate(TESLA::Vector(0, 3, 8));
}

float camSpeed = 0.1f;

void UpdateLoop(float deltaTime)
{
	suzanne->Rotate(0.01f, TESLA::Vector(0, 1, 0));
	if(App::IsKeyPressed('A'))
	{
		mainCamera->Translate({-camSpeed, 0, 0});
	}
	if(App::IsKeyPressed('D'))
	{
		mainCamera->Translate({camSpeed, 0, 0});
	}
	if(App::IsKeyPressed('W'))
	{
		mainCamera->Translate({0, 0, -camSpeed});
	}
	if(App::IsKeyPressed('S'))
	{
		mainCamera->Translate({0, 0, camSpeed});
	}
	if(App::IsKeyPressed(VK_CONTROL))
	{
		mainCamera->Translate({0, -camSpeed, 0});
	}
	if(App::IsKeyPressed(VK_SPACE))
	{
		mainCamera->Translate({0, camSpeed, 0});
	}
	
	if(App::IsKeyPressed(VK_LBUTTON))
	{
		if(debounce) return;
		debounce = true;
		std::cout << "Left clicked \n";
	}
	else
	{
		if(!debounce) return;
		std::cout << "Left released \n";
		debounce = false;
	}
}

void CleanUp()
{	
	delete(suzanne);
}
