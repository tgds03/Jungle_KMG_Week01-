#include "stdafx.h"
#include "UPlaneComponent.h"
#include "./Framework/Core/CRenderer.h"

UPlaneComponent::UPlaneComponent() {
	vertices = 
	{
		//   x,   y,   z       r,   g,   b,   a
		{-1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, // ���ϴ� (����)
		{ 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f }, // ���ϴ� (�ʷ�)
		{ 1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f }, // ���� (�Ķ�)
		{-1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // �»�� (���)
	};
	
	indices = 
	{
		0, 1, 2,  // ù ��° �ﰢ��
		0, 2, 3   // �� ��° �ﰢ��
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
