#include "stdafx.h"
#include "UCubeComponent.h"
#include "./Framework/Core/CRenderer.h"

UCubeComponent::UCubeComponent() {
	//vertices = {
	//	{-1.f, -1.f, -1.f,	1.f, 0.f, 0.f, 1.f},
	//	{-1.f, -1.f, 1.f,	0.f, 1.f, 0.f, 1.f},
	//	{-1.f, 1.f, -1.f,	0.f, 0.f, 1.f, 1.f},
	//	{-1.f, 1.f, 1.f,	1.f, 1.f, 0.f, 1.f},
	//	{1.f, -1.f, -1.f,	0.f, 1.f, 1.f, 1.f},
	//	{1.f, -1.f, 1.f,	1.f, 0.f, 1.f, 1.f},
	//	{1.f, 1.f, -1.f,	1.f, 1.f, 1.f, 1.f},
	//	{1.f, 1.f, 1.f,		0.f, 0.f, 0.f, 1.f}
	//};

	//indices = {
	//	// Front face
	//	0, 2, 6,  0, 6, 4,
	//	// Back face
	//	1, 5, 7,  1, 7, 3,
	//	// Left face
	//	0, 4, 5,  0, 5, 1,
	//	// Right face
	//	2, 3, 7,  2, 7, 6,
	//	// Top face
	//	4, 6, 7,  4, 7, 5,
	//	// Bottom face
	//	0, 1, 3,  0, 3, 2
	//};

	vertices = {
		{-0.5f, -0.5f, 0.f,	1.f, 0.f, 0.f, 1.f},
		{-0.5f, 0.5f, 0.f,	1.f, 0.f, 0.f, 1.f},
		{0.5f, -0.5f, 0.f,	1.f, 0.f, 0.f, 1.f},
		{0.5f, 0.5f, 0.f,		1.f, 0.f, 0.f, 1.f},
	};

	indices =
	{
		0, 1, 2,  // 첫 번째 삼각형 (Bottom Left -> Top Left -> Bottom Right)
		1, 3, 2   // 두 번째 삼각형 (Top Left -> Top Right -> Bottom Right)
	};

	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	_vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
	_vertexBuffer->Create(vertices);
	_indexBuffer = new CIndexBuffer(graphics->GetDevice());
	_indexBuffer->Create(indices);
}

UCubeComponent::~UCubeComponent() {
	//SafeRelease(&_vertexBuffer);
	//SafeRelease(&_indexBuffer);
}
