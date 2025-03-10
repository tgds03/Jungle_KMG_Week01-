#include "stdafx.h"
#include "UCubeComponent.h"

UCubeComponent::UCubeComponent() {

	vertices = {
		{1.f, 1.f, -1.f, 1.f, 0.f, 0.f, 1.f},   // Vertex 0.
	{ -1.f, 1.f, -1.f, 0.f, 1.f, 0.f, 1.f },  // Vertex 1.
	{-1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f },    // And so on.
	{1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f},
	{1.f, -1.f, -1.f,1.f, 0.f, 1.f, 1.f},
	{-1.f, -1.f, -1.f, 0.f, 1.f, 1.f, 1.f},
	{-1.f, -1.f, 1.f, 0.f, 0.f, 0.f, 1.f},
	{1.f, -1.f, 1.f, 1.f, 1.f, 1.f, 1.f},
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


	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	_vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
	_vertexBuffer->Create(vertices);
	_indexBuffer = new CIndexBuffer(graphics->GetDevice());
	_indexBuffer->Create(indices);
}

void UCubeComponent::Update() {
	//RelativeRotation += FVector(1.f, 1.f, 1.f) * Time::GetDeltaTime();
	//RelativeLocation.x = sin(Time::GetElapsedTime());
}

