#include <array>
#include "NextAPI/app.h"
#include "Math.h"

TESLA::Mesh* cube;
TESLA::Matrix4x4* projection;
constexpr float cubeSize = 2;

constexpr float nearPlane = 0.1f;
constexpr float farPlane = 1000.0f;
constexpr float fov = 90.0f;
constexpr float aspectRatio = GLUT_SCREEN_HEIGHT/GLUT_SCREEN_WIDTH;
const float fovRad = 1.0f / tan(fov/2 / PI * 180);

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	TESLA::Vector bottomLeft = TESLA::Vector(-1, -1, -1) * cubeSize * 100;
	TESLA::Vector bottomRight = TESLA::Vector(1, -1, -1) * cubeSize * 100;

	TESLA::Vector topLeft = TESLA::Vector(-1, 1, -1) * cubeSize * 100;
	TESLA::Vector topRight = TESLA::Vector(1, 1, -1) * cubeSize * 100;

	TESLA::Vector bottomLeftBack = TESLA::Vector(-1, -1, 1) * cubeSize * 100;
	TESLA::Vector bottomRightBack = TESLA::Vector(1, -1, 1) * cubeSize * 100;

	TESLA::Vector topLeftBack = TESLA::Vector(-1, 1, 1) * cubeSize * 100;
	TESLA::Vector topRightBack = TESLA::Vector(1, 1, 1) * cubeSize * 100;
	
	const std::vector<TESLA::Triangle> triangles
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

	projection = new TESLA::Matrix4x4{
		{aspectRatio * fovRad, 0.0f, 0.f, 0.0f},
		{0.0f, fovRad, 0.0f, 0.0f},
		{0.0f, 0.0f, farPlane/(farPlane - nearPlane), 1.0f},
		{0.0f, 0.0f, -farPlane * nearPlane/(farPlane - nearPlane), 0.0f}
	};

	cube = new TESLA::Mesh(triangles);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
float accumulatedTime;
void Update(float deltaTime)
{
	accumulatedTime += 1 * deltaTime/1000;
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	float sinTheta = static_cast<float>(sin(accumulatedTime));
	float cosTheta = static_cast<float>(cos(accumulatedTime));
	
	TESLA::Matrix4x4 rotationY
	{
		{cosTheta, 0.0f, -sinTheta, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{sinTheta, 0.0f, cosTheta, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	TESLA::Matrix4x4 rotationX
	{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, cosTheta, sinTheta, 0.0f},
		{0.0f, -sinTheta, cosTheta, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	TESLA::Matrix4x4 rotationZ
	{
		{cosTheta, sinTheta, 0.0f, 0.0f},
		{-sinTheta, cosTheta, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};
	
	for (TESLA::Triangle triangle : cube->triangles)
	{
		TESLA::Triangle triangleProjected;

		triangleProjected.vertices[0] = triangle.vertices[0] * rotationX * rotationY * rotationZ * *projection;
		triangleProjected.vertices[1] =	triangle.vertices[1] * rotationX * rotationY * rotationZ * *projection;
		triangleProjected.vertices[2] =	triangle.vertices[2] * rotationX * rotationY * rotationZ * *projection;

		triangleProjected.vertices[0].x += 500.0f;
		triangleProjected.vertices[0].y += 250.0f;
		triangleProjected.vertices[1].x += 500.0f;
		triangleProjected.vertices[1].y += 250.0f;
		triangleProjected.vertices[2].x += 500.0f;
		triangleProjected.vertices[2].y += 250.0f;
	
		App::DrawLine(triangleProjected.vertices[0].x, triangleProjected.vertices[0].y,
			triangleProjected.vertices[1].x, triangleProjected.vertices[1].y);
	
		App::DrawLine(triangleProjected.vertices[1].x, triangleProjected.vertices[1].y,
			triangleProjected.vertices[2].x, triangleProjected.vertices[2].y);
	
		// App::DrawLine(triangleProjected.vertices[2].x, triangleProjected.vertices[2].y,
		// 	triangleProjected.vertices[0].x, triangleProjected.vertices[0].y);
	}
	
	App::Print(100, 100, "Amogus");
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	delete(cube);
	delete(projection);
}
