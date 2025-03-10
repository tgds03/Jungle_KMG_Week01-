#pragma once
#include "Framework/Core/UPrimitiveComponent.h"

class UDiscHollowHalfComponent :
    public UPrimitiveComponent
{
public:
    UDiscHollowHalfComponent(EPrimitiveColor color, float innerRadius);
    UDiscHollowHalfComponent();
    ~UDiscHollowHalfComponent();
    //virtual void Update();
    //virtual bool Intersects(const FVector& rayOrigin, const FVector& rayDir, float& dist);
    //virtual bool PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance) override;
    virtual bool IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist);

    float inner;

};
