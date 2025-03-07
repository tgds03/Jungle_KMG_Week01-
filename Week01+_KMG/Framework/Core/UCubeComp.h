#pragma once
#include "Framework/Core/UPrimitiveComponent.h"
class UCubeComp :
    public UPrimitiveComponent
{
public:
    virtual void Update();
    virtual void Render();

private:
    FVector Extent; // x,y,z방향으로의 크기. Transform의 Scale이 아님
public:
    void SetExtent(FVector extent);
};

