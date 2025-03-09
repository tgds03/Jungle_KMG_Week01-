#include "stdafx.h"
#include "UPlaneComponent.h"
#include "./Framework/Core/CRenderer.h"

UPlaneComponent::UPlaneComponent() {
	vertices = 
	{
		//   x,   y,   z       r,   g,   b,   a
		{-1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, // 좌하단 (빨강)
		{ 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f }, // 우하단 (초록)
		{ 1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f }, // 우상단 (파랑)
		{-1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, // 좌상단 (흰색)
	};
	
	indices = 
	{
		0, 2, 1,  // 첫 번째 삼각형
		0, 3, 2   // 두 번째 삼각형
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

bool UPlaneComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist)
{
	// y=0일때 (x,z)는 를 지남 (-1,-1), (1,1)
	// y=0일떄의 (x,z)
	FVector4 o(rayOrigin, 1.f);
	FVector4 d(rayDir, 0.f);

	float x = o.x - d.x * (o.y / d.y);
	//float y = 0;
	float z = o.z - d.z * (o.y / d.y);

	return (-1 < x && x < 1 && -1 < z && z < 1);
}

void UPlaneComponent::PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance)
{

}

FVector UPlaneComponent::GetComponentNormal()
{
	FVector4 normal(0, 0, 1, 0);
	normal = normal * GetComponentTransform();
	return FVector(normal.xyz());
}
