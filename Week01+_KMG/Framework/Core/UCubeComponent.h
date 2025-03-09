#pragma once
#include "./Framework/Core/UPrimitiveComponent.h"
class UCubeComponent: public UPrimitiveComponent {
public:
	UCubeComponent();
	virtual ~UCubeComponent();
	virtual void Update();
	virtual bool IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, const FVector& boxCenter, FVector& boxHalfSize, FVector boxAxes[3], float& hitDistance);
    virtual void GenerateRayForPicking(const FVector& pickPosition, const FVector& rayDirection, const FMatrix& viewMatrix);

};