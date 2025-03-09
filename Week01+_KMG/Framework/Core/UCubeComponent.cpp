#include "stdafx.h"
#include "UCubeComponent.h"
#include "./Framework/Core/CRenderer.h"

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
bool UCubeComponent::IntersectsRay(
    const FVector& rayOrigin,
    const FVector& rayDir,
    const FVector& boxCenter,
    FVector& boxHalfSize,
    FVector boxAxes[3],
    float& hitDistance)
{
    const float epsilon = 1e-6f;
    float tMin = -FLT_MAX;
    float tMax = FLT_MAX;
    FVector p = rayOrigin - boxCenter;

    for (int i = 0; i < 3; i++) {
        float e = boxAxes[i].Dot(p);
        float f = boxAxes[i].Dot(rayDir);
		
        if (fabs(f) > epsilon) {
            float t1 = (-boxHalfSize[i] - e) / f;
            float t2 = (boxHalfSize[i] - e) / f;
            if (t1 > t2) {
                std::swap(t1, t2);
            }
            tMin = (t1 > tMin) ? t1 : tMin;
            tMax = (t2 < tMax) ? t2 : tMax;

			OutputDebugString((L"Axis " + std::to_wstring(i) + L": e=" + std::to_wstring(e) +
				L", f=" + std::to_wstring(f) + L", t1=" + std::to_wstring(t1) +
				L", t2=" + std::to_wstring(t2) + L"\n").c_str());
			OutputDebugString((L"Updated tMin=" + std::to_wstring(tMin) +
				L", tMax=" + std::to_wstring(tMax) + L"\n").c_str());

            if (tMin > tMax)
                return false;
            if (tMax < 0)
                return false;
        }
        else {
            // 레이가 평행한 경우, 현재 슬랩 내부에 있는지 확인
            if (e < -boxHalfSize[i] || e > boxHalfSize[i])
                return false;
        }
    }

    // hitDistance를 항상 할당한 후 반환
    hitDistance = (tMin >= 0) ? tMin : tMax;
    return true;
}

void UCubeComponent::GenerateRayForPicking(const FVector& pickPosition, const FVector& rayDirection, const FMatrix& viewMatrix)
{
	FMatrix invViewMatrix = viewMatrix.Inverse();
	FVector worldCameraOrigin = invViewMatrix.TransformCoord(FVector4(0, 0, 0, 1));
	FVector worldPickPos = invViewMatrix.TransformCoord(FVector4(pickPosition, 1));
	FVector worldPickDir = (worldPickPos - worldCameraOrigin).Normalized();

	FMatrix compMatrix = GetComponentTransform();
	FVector boxCenter = { compMatrix[3][0], compMatrix[3][1], compMatrix[3][2] };

	FVector localHalfSize = FVector(0.5f, 0.5f, 0.5f); // 큐브의 스케일 반영

	FMatrix worldMatrix = GetComponentTransform();
	FVector boxAxes[3] = {
		compMatrix.GetScaledAxis(EAxis::X).Normalized(),
		compMatrix.GetScaledAxis(EAxis::Y).Normalized(),
		compMatrix.GetScaledAxis(EAxis::Z).Normalized()
	};

	float hitDistance = 0.f;
	bool bHit = IntersectsRay(worldCameraOrigin, rayDirection, boxCenter, localHalfSize, boxAxes, hitDistance);

	if (bHit)
	{
		OutputDebugString(L"hit!!!!\n");
	}
	else
	{
		OutputDebugString(L"Ray did not hit the cube\n");
	}

	// 디버깅 출력 (월드 좌표계 기준)
	OutputDebugString((L"World Pick Position\n"));
	OutputDebugString((L"x: " + std::to_wstring(worldPickPos.x) + L"\n").c_str());
	OutputDebugString((L"y: " + std::to_wstring(worldPickPos.y) + L"\n").c_str());
	OutputDebugString((L"z: " + std::to_wstring(worldPickPos.z) + L"\n").c_str());

	OutputDebugString((L"Pick Ray Direction (World Space)\n"));
	OutputDebugString((L"x: " + std::to_wstring(rayDirection.x) + L"\n").c_str());
	OutputDebugString((L"y: " + std::to_wstring(rayDirection.y) + L"\n").c_str());
	OutputDebugString((L"z: " + std::to_wstring(rayDirection.z) + L"\n").c_str());
}
