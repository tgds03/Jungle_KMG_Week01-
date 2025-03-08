#include "stdafx.h"
#include "UCubeComponent.h"

UCubeComponent::UCubeComponent() {
	vertices =
	{
		// Front Face (�ո�)
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f },

		// Back Face (�޸�)
		{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f }
	};

	indices =
	{
		// Front Face (�ո�)
		0, 1, 2,  1, 3, 2,

		// Back Face (�޸�)
		4, 5, 6,  5, 7, 6,

		// Left Face (���ʸ�)
		4, 6, 0,  6, 1, 0,

		// Right Face (�����ʸ�)
		2, 3, 5,  3, 7, 5,

		// Top Face (����)
		1, 6, 3,  6, 7, 3,

		// Bottom Face (�Ʒ���)
		0, 2, 4,  2, 5, 4
	};

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
	//	0, 1, 2,  // ù ��° �ﰢ�� (Bottom Left -> Top Left -> Bottom Right)
	//	1, 3, 2   // �� ��° �ﰢ�� (Top Left -> Top Right -> Bottom Right)
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
