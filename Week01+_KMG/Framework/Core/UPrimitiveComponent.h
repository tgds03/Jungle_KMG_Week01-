#pragma once
#include "USceneComponent.h"
#include "./Framework/DirectXWrapper/CBuffer.h"
#include "./Framework/DirectXWrapper/CInputLayout.h"
#include "./Framework/Core/CRenderer.h"

class UPrimitiveComponent: public USceneComponent {
public:
	UPrimitiveComponent(): renderFlags(0) {}
	TArray<FVertexSimple> vertices;
	TArray<uint32> indices;

	virtual void Render();
	virtual bool IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist) { return false; }
	virtual void GenerateRayForPicking(const FVector& pickPosition, const FMatrix& viewMatrix, FVector* pickRayOrigin, FVector* rayDirection) override;
	virtual bool PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance) override;

	uint32 renderFlags;
protected:
	CVertexBuffer<FVertexSimple>* _vertexBuffer = nullptr;
	CIndexBuffer* _indexBuffer = nullptr;
};