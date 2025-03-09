#pragma once
#include "./Framework/Core/UPrimitiveComponent.h"
class UCubeComponent: public UPrimitiveComponent {
public:
	UCubeComponent();
	virtual ~UCubeComponent();
	virtual void Update();
	virtual bool IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist);
    virtual void PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance) override;

};