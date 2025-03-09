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
		0, 2, 1,  // ù ��° �ﰢ��
		0, 3, 2   // �� ��° �ﰢ��
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
	// y=0�϶� (x,z)�� �� ���� (-1,-1), (1,1)
	// y=0�ϋ��� (x,z)
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
