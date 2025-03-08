#pragma once
#include "Framework/DirectXWrapper/CBuffer.h"
#include "FrameWork/Core/USceneComponent.h"
#include "FrameWork/Core/FVertexSimple.h"
#include "CRenderer.h"
#include "Framework/DirectXWrapper/CShader.h"
#include "Framework/DirectXWrapper/CInputLayout.h"
#include "Framework/DirectXWrapper/CState.h"
#include "Framework/Core/UStaticMesh.h"

class UPrimitiveComponent :
    public USceneComponent
{
public:
    UPrimitiveComponent();
    virtual void Init(CVertexShader* vertexShader, CPixelShader* pixelShader, UStaticMesh* mesh);
    virtual void Update();
    virtual void Render();

// 렌더 관련
protected:
    bool bVisible = true;
public:
    void setVisible(const bool bValue);


public:
    bool bSelectable = true;
    
    UStaticMesh* Mesh = nullptr;

    


    // 일단 쉐이더 여기에 (분리해야하나?)
    CVertexShader* VertexShader = nullptr;
    CPixelShader* PixelShader = nullptr;
    InputLayout* inputLayout = nullptr;
    CConstantBuffer<FMatrix>* ConstantBuffer = nullptr;
    CRasterizerState* RasterizerState = nullptr;
    CSamplerState* SamplerState = nullptr;
};

