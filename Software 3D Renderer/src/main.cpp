#include <iostream>
#include "../../NextAPI/NextAPI/app.h"
#include "Tesla/Core/EntryPoint.h"
#include "Tesla/Mesh/Mesh.h"
#include "Tesla/Math/Math.h"

TESLA::Mesh* cube;
TESLA::Mesh* cube2;

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
		{bottomLeft, topLeft, topRight},
		{topRight, bottomRight, bottomLeft},

		//Back
		{ bottomLeftBack, topLeftBack, topRightBack},
		{topRightBack, bottomRightBack, bottomLeftBack},

		//Left
		{topLeftBack, topLeft, bottomLeft},
		{bottomLeft, bottomLeftBack, topLeftBack},

		//Right
		{topRight, topRightBack, bottomRightBack},
		{bottomRightBack, bottomRight, topRight},

		//Up
		{topLeftBack, topRightBack, topRight},
		{topRight, topLeft, topLeftBack},

		//Down
		{bottomRightBack, bottomLeftBack, bottomLeft},
		{bottomLeft, bottomRight, bottomRightBack},
	};

	cube = new TESLA::Mesh(triangles);
	cube->Scale(cubeSize, TESLA::Vector(1,1,1));
	cube->Translate(TESLA::Vector(0, 3, 8));

	cube2 = new TESLA::Mesh(triangles);
	cube2->Scale(cubeSize/2, TESLA::Vector(1, 1, 1));
	cube2->Translate(TESLA::Vector(0,0,3));
}

float camSpeed = 0.1f;

void UpdateLoop(float deltaTime)
{
	cube->Rotate(0.01f, TESLA::Vector(0, 1, 0));
	cube2->Rotate(0.001f, TESLA::Vector(1, 1, 1));
	
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
