#pragma once
#include "Framework/DirectXWrapper/CBuffer.h"
#include "FrameWork/Core/USceneComponent.h"
#include "FrameWork/Core/FVertexSimple.h"

class UPrimitiveComponent :
    public USceneComponent
{
public:
    virtual void Update();
    virtual void Render();

// ·»´õ °ü·Ã
protected:
    bool bVisible = true;
public:
    void setVisible(const bool bValue);

public:
    bool bSelectable = true;
    CVertexBuffer<FVertexSimple>* VertexBuffer;
    TArray<FVertexSimple> Vertices;
};

