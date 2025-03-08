#include "stdafx.h"
#include "UPlaneComponent.h"
#include "./Framework/Core/CRenderer.h"

UPlaneComponent::UPlaneComponent() {
	vertices = 
	{
		//   x,   y,   z       r,   g,   b,   a
		{-1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, // ÁÂÇÏ´Ü (»¡°­)
		{ 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f }, // ¿ìÇÏ´Ü (ÃÊ·Ï)
		{ 1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f }, // ¿ì»ó´Ü (ÆÄ¶û)
		{-1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // ÁÂ»ó´Ü (Èò»ö)
	};
	
	indices = 
	{
		0, 1, 2,  // Ã¹ ¹øÂ° »ï°¢Çü
		0, 2, 3   // µÎ ¹øÂ° »ï°¢Çü
	};

	//vertices = {
	//	{10.f, -5.f, 10.f,		1.f, 0.f, 0.f, 1.f},
	//	{-10.f, -5.f, 10.f,		0.f, 1.f, 0.f, 1.f},
	//	{-10.f, -5.f, -10.f,	0.f, 0.f, 1.f, 1.f },
	//	{10.f, -5.f, -10.f,		1.f, 1.f, 1.f, 1.f }
	//};

	//indices = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	_vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
	_vertexBuffer->Create(vertices);
	_indexBuffer = new CIndexBuffer(graphics->GetDevice());
	_indexBuffer->Create(indices);
}

UPlaneComponent::~UPlaneComponent() {
	delete _vertexBuffer;
	delete _indexBuffer;
}
