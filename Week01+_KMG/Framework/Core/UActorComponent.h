#pragma once
#include "Framework/Core/UObject.h"

class UWorld;

class UActorComponent :public UObject {	
public:
	UActorComponent() {}
	virtual ~UActorComponent() {}

	virtual void Update() {};
	virtual void Render() {};

	virtual bool IntersectsRay(const FVector& rayOrigin, const  FVector& rayDir,
		const FVector& boxCenter, const  FVector& boxHalfSize,
		const  FVector boxAxes[3], float& hitDistance) {
		return false;
	}
	virtual void GenerateRayForPicking(const FVector& pickPosition,const FVector& rayDirection,const FMatrix& viewMatrix) {}
	static void GenerateAllRayForPicking(FVector& pickPosition, FVector& rayDirection, const FMatrix& viewMatrix);

private:
	UWorld* motherScene;
};

