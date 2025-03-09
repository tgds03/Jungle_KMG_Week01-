#include "stdafx.h"
#include "UCubeComponent.h"
#include "./Framework/Core/CRenderer.h"

UCubeComponent::UCubeComponent() {
	//vertices =
	//{
	//	// Front Face (¾Õ¸é)
	//	{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
	//	{ -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//	{ 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//	{ 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f },

	//	// Back Face (µÞ¸é)
	//	{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f },
	//	{ 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
	//	{ -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
	//	{ 0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f }
	//};

	//indices =
	//{
	//	// Front Face (¾Õ¸é)
	//	0, 1, 2,  1, 3, 2,

	//	// Back Face (µÞ¸é)
	//	4, 5, 6,  5, 7, 6,

	//	// Left Face (¿ÞÂÊ¸é)
	//	4, 6, 0,  6, 1, 0,

	//	// Right Face (¿À¸¥ÂÊ¸é)
	//	2, 3, 5,  3, 7, 5,

	//	// Top Face (À­¸é)
	//	1, 6, 3,  6, 7, 3,

	//	// Bottom Face (¾Æ·§¸é)
	//	0, 2, 4,  2, 5, 4
	//};

	vertices = {
		{1.f, 1.f, -1.f, 1.f, 0.f, 0.f, 1.f},   // Vertex 0.
	{ -1.f, 1.f, -1.f, 1.f, 0.f, 0.f, 1.f },  // Vertex 1.
	{-1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f },    // And so on.
	{1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f},
	{1.f, -1.f, -1.f,1.f, 0.f, 0.f, 1.f},
	{-1.f, -1.f, -1.f, 1.f, 0.f, 0.f, 1.f},
	{-1.f, -1.f, 1.f, 1.f, 0.f, 0.f, 1.f},
	{1.f, -1.f, 1.f, 1.f, 0.f, 0.f, 1.f},
	};

	indices =
	{
	0,1,2,               // Face 0 has three vertices.
	0,2,3,                // And so on.
	0,4,5,
	0,5,1,
	1,5,6,
	1,6,2,
	2,6,7,
	2,7,3,
	3,7,4,
	3,4,0,
	4,7,6,
	4,6,5,
	};

	//vertices = {
	//	{-0.5f, -0.5f, 0.f,	1.f, 0.f, 0.f, 1.f},
	//	{-0.5f, 0.5f, 0.f,	1.f, 0.f, 0.f, 1.f},
	//	{0.5f, -0.5f, 0.f,	1.f, 0.f, 0.f, 1.f},
	//	{0.5f, 0.5f, 0.f,	1.f, 0.f, 0.f, 1.f},
	//};

	//indices =
	//{
	//	0, 1, 2,  // Ã¹ ¹øÂ° »ï°¢Çü (Bottom Left -> Top Left -> Bottom Right)
	//	1, 3, 2   // µÎ ¹øÂ° »ï°¢Çü (Top Left -> Top Right -> Bottom Right)
	//};

	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	_vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
	_vertexBuffer->Create(vertices);
	_indexBuffer = new CIndexBuffer(graphics->GetDevice());
	_indexBuffer->Create(indices);
}

UCubeComponent::~UCubeComponent() {
	delete _vertexBuffer;
	delete _indexBuffer;
}

void UCubeComponent::Update() {
	//RelativeRotation += FVector(1.f, 1.f, 1.f) * Time::GetDeltaTime();
	//RelativeLocation.x = sin(Time::GetElapsedTime());
}

bool UCubeComponent::Intersects(FVector rayOrigin, FVector rayDirection)
{
	FVector4 rayOrigin4(rayOrigin, 1.f);
	rayOrigin4 = rayOrigin4 * GetComponentTransform().Inverse();
	rayOrigin4 = rayOrigin4 / rayOrigin4.w;

	FVector4 rayDirection4(rayDirection, 0.f);
	rayDirection4 = rayDirection4 * GetComponentTransform().Inverse();

	float t_min_x = (-1 - rayOrigin4.x) / rayDirection4.x;
	float t_max_x = (1 - rayOrigin4.x) / rayDirection4.x;
	if (rayDirection4.x < 0) std::swap(t_min_x, t_max_x);

	float t_min_y = (-1 - rayOrigin4.y) / rayDirection4.y;
	float t_max_y = (1 - rayOrigin4.y) / rayDirection4.y;
	if (rayDirection4.y < 0) std::swap(t_min_y, t_max_y);

	float t_min_z = (-1 - rayOrigin4.z) / rayDirection4.z;
	float t_max_z = (1 - rayOrigin4.z) / rayDirection4.z;
	if (rayDirection4.z < 0) std::swap(t_min_z, t_max_z);
	
	float max_of_t_min = max(max(t_min_x, t_min_y), t_min_z);
	float min_of_t_max = min(min(t_max_x, t_max_y), t_max_z);

	return (max_of_t_min <= min_of_t_max) && (min_of_t_max >= 0);
}