#include "stdafx.h"
#include "UCubeComponent.h"
#include "./Framework/Core/CRenderer.h"

UCubeComponent::UCubeComponent() {
	vertices =
	{
		// Front Face (¾Õ¸é)
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f },

		// Back Face (µÞ¸é)
		{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f }
	};

	indices =
	{
		// Front Face (¾Õ¸é)
		0, 1, 2,  1, 3, 2,

		// Back Face (µÞ¸é)
		4, 5, 6,  5, 7, 6,

		// Left Face (¿ÞÂÊ¸é)
		4, 6, 0,  6, 1, 0,

		// Right Face (¿À¸¥ÂÊ¸é)
		2, 3, 5,  3, 7, 5,

		// Top Face (À­¸é)
		1, 6, 3,  6, 7, 3,

		// Bottom Face (¾Æ·§¸é)
		0, 2, 4,  2, 5, 4
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
