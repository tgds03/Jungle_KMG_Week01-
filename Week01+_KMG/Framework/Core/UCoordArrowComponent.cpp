//#include "UCoordArrowComponent.h"
//
//
//UCoordArrowComponent::UCoordArrowComponent()
//{
//	static const vertices =
//	{
//		{0,0,0,1,0,0,1},
//		{1,0,0,1,0,0,1},
//		{0,1,0,0,1,0,1},
//		{0,1,0,0,1,0,1},
//		{0,0,1,0,0,1,1},
//		{0,0,1,0,0,1,1},
//	}
//}
//
//UCoordArrowComponent::~UCoordArrowComponent()
//{
//}
//
//void UCoordArrowComponent::Render()
//{
//
//}
//
//void UCoordArrowComponent::Update()
//{
//}
//

#include "stdafx.h"
#include "UCoordArrowComponent.h"
#include "./Framework/Core/CRenderer.h"

UCoordArrowComponent::UCoordArrowComponent()
{
	vertices =
	{
		{ 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f},
		{ 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f},
		{ 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f},
		{ 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f},
		{ 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f},
		{ 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f},
	};

	indices = { 0,1,2,3,4,5 };

	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	_vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
	_vertexBuffer->Create(vertices);
	_indexBuffer = new CIndexBuffer(graphics->GetDevice());
	_indexBuffer->Create(indices);
}

UCoordArrowComponent::~UCoordArrowComponent()
{
	delete _vertexBuffer;
	delete _indexBuffer;
}

void UCoordArrowComponent::Update()
{
}

void UCoordArrowComponent::Render()
{
	//if(RelativeLocation)
	//D3D11_RASTERIZER_DESC RSDesc;
	//RSDesc.FillMode = D3D11_FILL_WIREFRAME;
	//RSDesc.CullMode = D3D11_CULL_NONE;
	//ID3D11RasterizerState *lineMode = nullptr;

	//auto device = CRenderer::Instance()->GetGraphics()->GetDevice();
	//device->CreateRasterizerState()

	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	CRenderer::Instance()->SetRasterzierState();
	ID3D11Buffer* vertexBuffer = _vertexBuffer->Get();
	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	graphics->GetDeviceContext()->IASetIndexBuffer(_indexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);
	FMatrix m = GetComponentTransform();
	CRenderer::Instance()->SetConstantBuffer(m);
	graphics->GetDeviceContext()->DrawIndexed(indices.size(), 0, 0);
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
