#include "stdafx.h"
#include "UCubeComponent.h"

UCubeComponent::UCubeComponent() {
	vertices =
	{
		// Front Face (앞면)
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f },

		// Back Face (뒷면)
		{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f }
	};

	indices =
	{
		// Front Face (앞면)
		0, 1, 2,  1, 3, 2,

		// Back Face (뒷면)
		4, 5, 6,  5, 7, 6,

		// Left Face (왼쪽면)
		4, 6, 0,  6, 1, 0,

		// Right Face (오른쪽면)
		2, 3, 5,  3, 7, 5,

		// Top Face (윗면)
		1, 6, 3,  6, 7, 3,

		// Bottom Face (아랫면)
		0, 2, 4,  2, 5, 4
	};

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
	//	0, 1, 2,  // 첫 번째 삼각형 (Bottom Left -> Top Left -> Bottom Right)
	//	1, 3, 2   // 두 번째 삼각형 (Top Left -> Top Right -> Bottom Right)
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
bool UCubeComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& Distance)
{
	// AABB 최소, 최대 좌표 정의
	FVector min = { -1.f, -1.f, -1.f };
	FVector max = { 1.f,  1.f,  1.f };

	// t 값의 범위를 초기화
	float tMin = -FLT_MAX;
	float tMax = FLT_MAX;
	const float epsilon = 1e-6f; // 0과의 비교를 위한 작은 값

	// x축에 대한 슬랩 테스트
	if (fabs(rayDir.x) < epsilon)
	{
		if (rayOrigin.x < min.x || rayOrigin.x > max.x)
			return false;
	}
	else
	{
		double t1 = (min.x - rayOrigin.x) / rayDir.x;
		double t2 = (max.x - rayOrigin.x) / rayDir.x;
		if (t1 > t2)
			std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	// y축에 대한 슬랩 테스트
	if (fabs(rayDir.y) < epsilon)
	{
		if (rayOrigin.y < min.y || rayOrigin.y > max.y)
			return false;
	}
	else
	{
		float t1 = (min.y - rayOrigin.y) / rayDir.y;
		float t2 = (max.y - rayOrigin.y) / rayDir.y;
		if (t1 > t2)
			std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	// z축에 대한 슬랩 테스트
	if (fabs(rayDir.z) < epsilon)
	{
		if (rayOrigin.z < min.z || rayOrigin.z > max.z)
			return false;
	}
	else
	{
		float t1 = (min.z - rayOrigin.z) / rayDir.z;
		float t2 = (max.z - rayOrigin.z) / rayDir.z;
		if (t1 > t2)
			std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	// 교차가 발생하는지 확인: tMax가 tMin보다 크거나 같고, tMax가 음수가 아니라면 교차가 있음.
	if (tMax >= tMin && tMax >= 0)
	{
		Distance = tMin;  // 필요에 따라 tMax를 사용할 수도 있음.
		return true;
	}

	return false;
}

void UCubeComponent::PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance)
{

	FVector pickRayOrigin, pickRayDirection;
	GenerateRayForPicking(pickPosition, viewMatrix, &pickRayOrigin, &pickRayDirection);



	

	// 디버깅 출력 (월드 좌표계 기준)
	OutputDebugString((L"pickRayOrigin ---------------------------------\n"));
	OutputDebugString((L"x: " + std::to_wstring(pickRayOrigin.x) + L"\n").c_str());
	OutputDebugString((L"y: " + std::to_wstring(pickRayOrigin.y) + L"\n").c_str());
	OutputDebugString((L"z: " + std::to_wstring(pickRayOrigin.z) + L"\n").c_str());

	OutputDebugString((L"pickRayDirection---------------------------------\n"));
	OutputDebugString((L"x: " + std::to_wstring(pickRayDirection.x) + L"\n").c_str());
	OutputDebugString((L"y: " + std::to_wstring(pickRayDirection.y) + L"\n").c_str());
	OutputDebugString((L"z: " + std::to_wstring(pickRayDirection.z) + L"\n").c_str());
	bool bHit = IntersectsRay(pickRayOrigin, pickRayDirection, *hitDistance);

	if (bHit)
	{
		OutputDebugString(L"Res :: hit!!!!-----------------\n");
	}
	else
	{
		OutputDebugString(L"Res :: NOT!!!!-----------------\n");
		//OutputDebugString(L"Ray did not hit the cube\n");
	}
}
