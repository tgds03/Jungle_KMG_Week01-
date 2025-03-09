#pragma once
#include "./Framework/Core/UPrimitiveComponent.h"

class UPlaneComponent :public UPrimitiveComponent {
public:
	UPlaneComponent();
	virtual ~UPlaneComponent();
	virtual bool IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist);
	virtual void PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance) override;

private:
	FVector GetComponentNormal();
};

