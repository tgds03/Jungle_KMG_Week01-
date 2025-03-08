#include "stdafx.h"
#include "UCubeComp.h"

// cube vertex data
//TArray<FVertexSimple> vertices =
//{
//    FVertexSimple{-0.3f, -0.3f, -0.3f, 0.3f, 0.3f, 0.3f, 0.3f },
//    FVertexSimple{0.3f, -0.3f, -0.3f, 0.3f, 0.3f, 0.3f, 0.3f},
//    FVertexSimple{0.3f, 0.3f, -0.3f, 0.3f, 0.3f, 0.3f, 0.3f},
//    FVertexSimple{-0.3f, 0.3f, -0.3f, 0.3f, 0.3f, 0.3f, 0.3f},
//    FVertexSimple{-0.3f, -0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f},
//    FVertexSimple{0.3f, -0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f},
//    FVertexSimple{0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f},
//    FVertexSimple{-0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f}
//};
//
//
//TArray<UINT32> indices = {
//    0, 1, 3, 3, 1, 2,
//    1, 5, 2, 2, 5, 6,
//    5, 4, 6, 6, 4, 7,
//    4, 0, 7, 7, 0, 3,
//    3, 2, 7, 7, 2, 6,
//    4, 5, 0, 0, 5, 1
//};

TArray<FVertexSimple> vertices =
{
    FVertexSimple{-0.3f, -0.3f, 0.f, 1.f,1.f,1.f,1.f },
    FVertexSimple{-0.3f, 0.3f, 0.f, 1.f,1.f,1.f,1.f },
    FVertexSimple{0.3f, 0.3f, 0.f, 1.f,1.f,1.f,1.f },
    FVertexSimple{0.3f, -0.3f, 0.f, 1.f,1.f,1.f,1.f },
};

TArray<UINT32> indices = {
    0,1,2,2,3,0
};

void UCubeComp::Init(CVertexShader* vertexShader, CPixelShader* pixelShader)
{
    Mesh = new UStaticMesh(vertices, indices);
    Mesh->CreateBuffer();
    UPrimitiveComponent::Init(vertexShader, pixelShader, Mesh);
}

void UCubeComp::Update()
{

}

void UCubeComp::Render()
{
    UPrimitiveComponent::Render();
}

void UCubeComp::SetExtent(FVector extent)
{
}
