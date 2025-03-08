#pragma once
#include "./Framework/Core/UPrimitiveComponent.h"
class UCubeComponent: public UPrimitiveComponent {
public:
	UCubeComponent();
	virtual ~UCubeComponent();
	virtual void Update();
	virtual bool IntersectsRay(const FVector& rayOrigin, const  FVector& rayDir,
							   const FVector& boxCenter, const  FVector& boxHalfSize,
							   const  FVector boxAxes[3], float& hitDistance);

	virtual void GenerateRayForPicking(FVector& pickPosition, FMatrix& viewMatrix, FVector* pickRayOrigin, FVector* pickRayDirection);
};