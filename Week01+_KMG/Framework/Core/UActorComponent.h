#pragma once
#include "Framework/Core/UObject.h"

class UActorComponent :public UObject {	
public:
	UActorComponent();
	virtual ~UActorComponent();

	virtual void Update() {};
	virtual void Render() {};

	static void UpdateAll();
	static void RenderAll();
	virtual bool IntersectsRay(const FVector& rayOrigin, const  FVector& rayDir,
		const FVector& boxCenter, const  FVector& boxHalfSize,
		const  FVector boxAxes[3], float& hitDistance) {
		return false;
	}
	virtual void GenerateRayForPicking(FVector& pickPosition, FMatrix& viewMatrix, FVector* pickRayOrigin, FVector* pickRayDirection) {}
	static void GenerateAllRayForPicking(FVector& pickPosition, FMatrix& viewMatrix);
};

