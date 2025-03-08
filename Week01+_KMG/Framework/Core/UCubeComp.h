#pragma once
#include "Framework/Core/UPrimitiveComponent.h"
class UCubeComp :
    public UPrimitiveComponent
{
public:
    UCubeComp() : UPrimitiveComponent() {}
    virtual void Init(CVertexShader* vertexShader, CPixelShader* pixelShader);
    virtual void Update();
    virtual void Render();

private:
    FVector Extent; // x,y,z���������� ũ��. Transform�� Scale�� �ƴ�
public:
    void SetExtent(FVector extent);
};

