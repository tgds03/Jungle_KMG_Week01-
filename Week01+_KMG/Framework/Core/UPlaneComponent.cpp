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

bool UPlaneComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& Distance)
{
	FVector min = { -1.f, 0.f, -1.f };
	FVector max = { 1.f,  0.f,  1.f };

	double tMin = -FLT_MAX;
	double tMax = FLT_MAX;
	const double epsilon = FLT_EPSILON;

	if (fabs(rayDir.x) < epsilon) {
		if (rayOrigin.x < min.x || rayOrigin.x > max.x)
			return false;
	}
	else {
		double t1 = (min.x - rayOrigin.x) / rayDir.x;
		double t2 = (max.x - rayOrigin.x) / rayDir.x;
		if (t1 > t2)
			std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	if (fabs(rayDir.y) < epsilon) {
		if (rayOrigin.y < min.y || rayOrigin.y > max.y)
			return false;
	}
	else {
		double t1 = (min.y - rayOrigin.y) / rayDir.y;
		double t2 = (max.y - rayOrigin.y) / rayDir.y;
		if (t1 > t2) std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	if (fabs(rayDir.z) < epsilon) {
		if (rayOrigin.z < min.z || rayOrigin.z > max.z)
			return false;
	}
	else
	{
		double t1 = (min.z - rayOrigin.z) / rayDir.z;
		double t2 = (max.z - rayOrigin.z) / rayDir.z;
		if (t1 > t2) std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	if (tMax >= tMin && tMax >= 0) {
		Distance = tMin;
		return true;
	}

	return false;
}
