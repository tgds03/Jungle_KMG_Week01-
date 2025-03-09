#include "stdafx.h"
#include "UCubeComponent.h"

UCubeComponent::UCubeComponent() {
	//vertices =
	//{
	//	// Front Face (�ո�)
	//	{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
	//	{ -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
	//	{ 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
	//	{ 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f },

	//	// Back Face (�޸�)
	//	{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f },
	//	{ 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
	//	{ -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
	//	{ 0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f }
	//};

	//indices =
	//{
	//	// Front Face (�ո�)
	//	0, 1, 2,  1, 3, 2,

	//	// Back Face (�޸�)
	//	4, 5, 6,  5, 7, 6,

	//	// Left Face (���ʸ�)
	//	4, 6, 0,  6, 1, 0,

	//	// Right Face (�����ʸ�)
	//	2, 3, 5,  3, 7, 5,

	//	// Top Face (����)
	//	1, 6, 3,  6, 7, 3,

	//	// Bottom Face (�Ʒ���)
	//	0, 2, 4,  2, 5, 4
	//};

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

bool UCubeComponent::Intersects(FVector rayOrigin, FVector rayDirection)
{
	FVector4 rayOrigin4(rayOrigin, 1.f);
	rayOrigin4 = rayOrigin4 * GetComponentTransform().Inverse();
	rayOrigin4 = rayOrigin4 / rayOrigin4.w;

	FVector4 rayDirection4(rayDirection, 0.f);
	rayDirection4 = rayDirection4 * GetComponentTransform().Inverse();

	float t_min_x = (-1 - rayOrigin4.x) / rayDirection4.x;
	float t_max_x = (1 - rayOrigin4.x) / rayDirection4.x;
	if (rayDirection4.x < 0) std::swap(t_min_x, t_max_x);

	float t_min_y = (-1 - rayOrigin4.y) / rayDirection4.y;
	float t_max_y = (1 - rayOrigin4.y) / rayDirection4.y;
	if (rayDirection4.y < 0) std::swap(t_min_y, t_max_y);

	float t_min_z = (-1 - rayOrigin4.z) / rayDirection4.z;
	float t_max_z = (1 - rayOrigin4.z) / rayDirection4.z;
	if (rayDirection4.z < 0) std::swap(t_min_z, t_max_z);
	
	float max_of_t_min = max(max(t_min_x, t_min_y), t_min_z);
	float min_of_t_max = min(min(t_max_x, t_max_y), t_max_z);

	return (max_of_t_min <= min_of_t_max) && (min_of_t_max >= 0);
}
bool UCubeComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& Distance)
{
	// AABB �ּ�, �ִ� ��ǥ ����
	FVector min = { -1.f, -1.f, -1.f };
	FVector max = { 1.f,  1.f,  1.f };

	// t ���� ������ �ʱ�ȭ
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

	// y�࿡ ���� ���� �׽�Ʈ
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
//
//bool UCubeComponent::PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance)
//{
//
//	FVector pickRayOrigin, pickRayDirection;
//	GenerateRayForPicking(pickPosition, viewMatrix, &pickRayOrigin, &pickRayDirection);
//
//	OutputDebugString((L"pickRayOrigin ---------------------------------\n"));
//	OutputDebugString((L"x: " + std::to_wstring(pickRayOrigin.x) + L"\n").c_str());
//	OutputDebugString((L"y: " + std::to_wstring(pickRayOrigin.y) + L"\n").c_str());
//	OutputDebugString((L"z: " + std::to_wstring(pickRayOrigin.z) + L"\n").c_str());
//
//	OutputDebugString((L"pickRayDirection---------------------------------\n"));
//	OutputDebugString((L"x: " + std::to_wstring(pickRayDirection.x) + L"\n").c_str());
//	OutputDebugString((L"y: " + std::to_wstring(pickRayDirection.y) + L"\n").c_str());
//	OutputDebugString((L"z: " + std::to_wstring(pickRayDirection.z) + L"\n").c_str());
//	bool bHit = IntersectsRay(pickRayOrigin, pickRayDirection, *hitDistance);
//
//	if (bHit)
//	{
//		OutputDebugString(L"Res :: hit!!!!-----------------\n");
//	}
//	else
//	{
//		OutputDebugString(L"Res :: NOT!!!!-----------------\n");
//		//OutputDebugString(L"Ray did not hit the cube\n");
//	}
//	return bHit;
//}
