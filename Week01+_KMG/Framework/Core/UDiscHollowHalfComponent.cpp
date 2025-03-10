#include "stdafx.h"
#include "UDiscHollowHalfComponent.h"

#define DISC_RESOLUTION 128

static const FVector Colors[] = {
    FVector(1.0f, 0.0f, 0.0f),  // X��: ����
    FVector(0.0f, 1.0f, 0.0f),  // Y��: �ʷ�
    FVector(0.0f, 0.0f, 1.0f)   // Z��: �Ķ�
};

UDiscHollowHalfComponent::UDiscHollowHalfComponent(EPrimitiveColor color, float innerRadius) : inner(innerRadius)
{
    inner = innerRadius;
    FVector color3 = Colors[color];

    if (vertices.empty())
    {
        float angleStep = 3.1415926535f / DISC_RESOLUTION;

        // 원의 외곽 버텍스 추가
        for (int i = 0; i <= DISC_RESOLUTION; ++i) {
            float angle = i * angleStep;
            float x = cos(angle);
            float z = sin(angle);
            vertices.push_back({ x, 0.0f, z ,color3.x, color3.y, color3.z, 1 });

            x *= innerRadius;
            z *= innerRadius;
            vertices.push_back({ x, 0.0f, z ,color3.x, color3.y, color3.z, 1 });
        }

        // 인덱스 설정 (삼각형 리스트)
        for (int i = 0; i <= DISC_RESOLUTION + 1; ++i) {
            int pivot = 2 * i;
            indices.push_back(pivot);      // 중심점
            indices.push_back(pivot + 3);      // 현재 점
            indices.push_back(pivot + 2);  // 다음 점 (마지막 점 예외 처리)

            indices.push_back(pivot);      // 중심점
            indices.push_back(pivot + 1);      // 현재 점
            indices.push_back(pivot + 3);  // 다음 점 (마지막 점 예외 처리)

        }
    }

    CGraphics* graphics = CRenderer::Instance()->GetGraphics();
    _vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
    _vertexBuffer->Create(vertices);
    _indexBuffer = new CIndexBuffer(graphics->GetDevice());
    _indexBuffer->Create(indices);
}

UDiscHollowHalfComponent::UDiscHollowHalfComponent()
{
    inner = 0.5;
    if (vertices.empty())
    {
        float angleStep =  3.1415926535f / DISC_RESOLUTION;

        // 원의 외곽 버텍스 추가
        for (int i = 0; i <= DISC_RESOLUTION; ++i) {
            float angle = i * angleStep;
            float x = cos(angle);
            float z = sin(angle);
            vertices.push_back({ x, 0.0f, z ,1,1,1, 1 });

            x *= 0.5;
            z *= 0.5;
            vertices.push_back({ x, 0.0f, z ,1,1,1, 1 });
        }

        // 인덱스 설정 (삼각형 리스트)
        for (int i = 0; i <= DISC_RESOLUTION + 1; ++i) {
            int pivot = 2 * i;
            indices.push_back(pivot);      // 중심점
            indices.push_back(pivot + 3);      // 현재 점
            indices.push_back(pivot + 2);  // 다음 점 (마지막 점 예외 처리)

            indices.push_back(pivot);      // 중심점
            indices.push_back(pivot + 1);      // 현재 점
            indices.push_back(pivot + 3);  // 다음 점 (마지막 점 예외 처리)

        }
        for (int i = 0; i <= DISC_RESOLUTION + 1; ++i) {
            int pivot = 2 * i;
            indices.push_back(pivot);      // 중심점
            indices.push_back(pivot + 2);      // 현재 점
            indices.push_back(pivot + 3);  // 다음 점 (마지막 점 예외 처리)

            indices.push_back(pivot);      // 중심점
            indices.push_back(pivot + 3);      // 현재 점
            indices.push_back(pivot + 1);  // 다음 점 (마지막 점 예외 처리)

        }

    }

    CGraphics* graphics = CRenderer::Instance()->GetGraphics();
    _vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
    _vertexBuffer->Create(vertices);
    _indexBuffer = new CIndexBuffer(graphics->GetDevice());
    _indexBuffer->Create(indices);
}

UDiscHollowHalfComponent::~UDiscHollowHalfComponent()
{
}

bool UDiscHollowHalfComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist)
{
    if (rayOrigin.y == 0) return false; // normal to normal vector of plane

    dist = -rayOrigin.y / rayDir.y;
    dist = dist > 0 ? dist : -dist;

    FVector intersectionPoint = rayOrigin + rayDir * dist;
    if (intersectionPoint.z < 0) return false; // intersection is on -y (which is empty half)
    float intersectionToDiscCenterSquared = intersectionPoint.MagnitudeSquared();

    return (inner * inner < intersectionToDiscCenterSquared && intersectionToDiscCenterSquared < 1);
}
