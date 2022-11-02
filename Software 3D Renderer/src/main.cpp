#include "Tesla/Core/EntryPoint.h"
#include "Tesla/Mesh/Mesh.h"
#include "Tesla/Math/Math.h"

TESLA::Mesh* cube;
TESLA::Mesh* cube2;

constexpr float cubeSize = 200;

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
	cube->Translate(TESLA::Vector(-600, -350, 0));

	cube2 = new TESLA::Mesh(triangles);
	cube2->Scale(cubeSize/2, TESLA::Vector(1, 1, 1));
	cube2->Translate(TESLA::Vector(-300, -200, 0));
}

void UpdateLoop(float deltaTime)
{
	cube->Rotate(0.05, TESLA::Vector(0, 1, 1));
	cube2->Rotate(0.025, TESLA::Vector(1, 1, 1));
}

void CleanUp()
{	
	delete(cube);
}
