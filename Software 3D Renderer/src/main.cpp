#include <iostream>
#include "../../NextAPI/NextAPI/app.h"
#include "Tesla/Core/EntryPoint.h"
#include "Tesla/Mesh/Mesh.h"
#include "Tesla/Math/Math.h"

TESLA::Mesh* cube;

constexpr float cubeSize = 2.0f;
bool debounce;

void Awake()
{
	TESLA::Vector bottomLeft = TESLA::Vector(-1, -1, -1);
	TESLA::Vector bottomRight = TESLA::Vector(1, -1, -1);

	TESLA::Vector topLeft = TESLA::Vector(-1, 1, -1);
	TESLA::Vector topRight = TESLA::Vector(1, 1, -1);

	TESLA::Vector bottomLeftBack = TESLA::Vector(-1, -1, 1);
	TESLA::Vector bottomRightBack = TESLA::Vector(1, -1, 1);

	TESLA::Vector topLeftBack = TESLA::Vector(-1, 1, 1);
	TESLA::Vector topRightBack = TESLA::Vector(1, 1, 1);
	
	std::vector<TESLA::Triangle> triangles
	{
		//Front
		{bottomLeft, bottomRight, topRight},
		{topRight, topLeft, bottomLeft},

		//Back
		{bottomLeftBack, topLeftBack, topRightBack},
		{topRightBack, bottomRightBack, bottomLeftBack},

		 //Left
		{bottomLeft, topLeft, topLeftBack},
		{topLeftBack, bottomLeftBack, bottomLeft},
		 
		  //Right
		{bottomRightBack, topRightBack, topRight},
		{topRight, bottomRight, bottomRightBack},
		 
		  //Bottom
		{bottomRightBack, bottomRight, bottomLeft},
		{bottomLeft, bottomLeftBack, bottomRightBack},
		 
		  //Top
		{topRight, topRightBack, topLeftBack},
		{topLeftBack, topLeft, topRight},
	};

	cube = new TESLA::Mesh(triangles);
	cube->Scale(cubeSize, TESLA::Vector(1,1,1));
	cube->Translate(TESLA::Vector(0, 3, 8));
}

float camSpeed = 0.1f;

void UpdateLoop(float deltaTime)
{
	cube->Rotate(0.01f, TESLA::Vector(1, 1, 1));
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
	delete(cube);
}
