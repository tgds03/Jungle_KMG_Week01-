#include "stdafx.h"
#include "UPlaneComponent.h"
#include "./Framework/Core/CRenderer.h"

UPlaneComponent::UPlaneComponent() {
	vertices = {
		{10.f, -5.f, 10.f,		1.f, 0.f, 0.f, 1.f},
		{-10.f, -5.f, 10.f,		0.f, 1.f, 0.f, 1.f},
		{-10.f, -5.f, -10.f,	0.f, 0.f, 1.f, 1.f },
		{10.f, -5.f, -10.f,		1.f, 1.f, 1.f, 1.f }
	};

	indices = {
		0, 1, 2,
		2, 3, 0
	};

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
