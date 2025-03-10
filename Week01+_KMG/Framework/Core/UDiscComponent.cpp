#include "stdafx.h"
#include "UDiscComponent.h"

#define DISC_RESOLUTION 64

static const FVector Colors[] = {
    FVector(1.0f, 0.0f, 0.0f),  // X��: ����
    FVector(0.0f, 1.0f, 0.0f),  // Y��: �ʷ�
    FVector(0.0f, 0.0f, 1.0f)   // Z��: �Ķ�
};

UDiscComponent::UDiscComponent(EPrimitiveColor color)
{
    FVector color3 = Colors[color];

    if (vertices.empty())
    {
        vertices.push_back({ 0.0f, 0.0f, 0.0f ,color3.x, color3.x, color3.x, 1 });

        float angleStep = 2.0f * 3.1415926535f / DISC_RESOLUTION;

        // 원의 외곽 버텍스 추가
        for (int i = 0; i <= DISC_RESOLUTION; ++i) {
            float angle = i * angleStep;
            float x = cos(angle);
            float z = sin(angle);
            vertices.push_back({ x, 0.0f, z ,color3.x, color3.y, color3.z, 1});
        }

        // 인덱스 설정 (삼각형 리스트)
        for (int i = 1; i <= DISC_RESOLUTION; ++i) {
            indices.push_back(0);      // 중심점
            indices.push_back(i+1);      // 현재 점
            indices.push_back(i);  // 다음 점 (마지막 점 예외 처리)
        }
    }

    CGraphics* graphics = CRenderer::Instance()->GetGraphics();
    _vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
    _vertexBuffer->Create(vertices);
    _indexBuffer = new CIndexBuffer(graphics->GetDevice());
    _indexBuffer->Create(indices);
}

UDiscComponent::UDiscComponent()
{
    if (vertices.empty())
    {
        vertices.push_back({ 0.0f, 0.0f, 0.0f });

        float angleStep = 2.0f * 3.1415926535f / DISC_RESOLUTION;

        // 원의 외곽 버텍스 추가
        for (int i = 0; i <= DISC_RESOLUTION; ++i) {
            float angle = i * angleStep;
            float x = cos(angle);
            float z = sin(angle);
            vertices.push_back({ x, 0.0f, z ,1,1,1,1 });
        }

        // 인덱스 설정 (삼각형 리스트)
        for (int i = 1; i <= DISC_RESOLUTION; ++i) {
            indices.push_back(0);      // 중심점
            indices.push_back(i + 1);      // 현재 점
            indices.push_back(i);  // 다음 점 (마지막 점 예외 처리)
        }
    }

    CGraphics* graphics = CRenderer::Instance()->GetGraphics();
    _vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
    _vertexBuffer->Create(vertices);
    _indexBuffer = new CIndexBuffer(graphics->GetDevice());
    _indexBuffer->Create(indices);
}

UDiscComponent::~UDiscComponent()
{
}

//void UDiscComponent::Update()
//{
//}

//bool UDiscComponent::PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance)
//{
//    FVector pickRayOrigin, pickRayDirection;
//    GenerateRayForPicking(pickPosition, viewMatrix, &pickRayOrigin, &pickRayDirection);
//
//    // viewspace에서 worldspace로 변환
//    FVector rayOriginWorld = (FVector4(pickRayOrigin, 1.f) * viewMatrix.Inverse())
//
//    bool bHit = Interse
//}

// world좌표계 ray -> model space에서 계산
//bool UDiscComponent::Intersects(const FVector rayOrigin, const FVector rayDir, float& dist)
//{
//    FMatrix worldTransformInv = GetComponentTransform().Inverse();
//    FVector rayOriginModel = (FVector4(rayOrigin, 1.f) * worldTransformInv).GetCoord();
//    FVector rayDirModel = (FVector4(rayDir, 0.f) * worldTransformInv).xyz();
//    
//    if (rayDirModel.y == 0) return false; // normal to normal vector of plane
//    dist = -rayOriginModel.y / rayDirModel.y;
//
//    FVector intersectionPoint = rayOriginModel + rayDirModel * dist;
//    float intersectionToDiscCenterSquared = intersectionPoint.MagnitudeSquared();
//
//    return (intersectionToDiscCenterSquared < 1);
//    assert(0);
//    return 0;
//}
 
// model space값을 받아옴
bool UDiscComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist)
{
    //FMatrix worldTransformInv = GetComponentTransform().Inverse();
    //FVector rayOriginModel = (FVector4(rayOrigin, 1.f) * worldTransformInv).GetCoord();
    //FVector rayDirModel = (FVector4(rayDir, 0.f) * worldTransformInv).xyz();

    if (rayOrigin.y == 0) return false; // normal to normal vector of plane

    dist = -rayOrigin.y / rayDir.y;

    FVector intersectionPoint = rayOrigin + rayDir * dist;
    float intersectionToDiscCenterSquared = intersectionPoint.MagnitudeSquared();

    return (intersectionToDiscCenterSquared < 1);
}
