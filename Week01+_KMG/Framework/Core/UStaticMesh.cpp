#include "stdafx.h"
#include "UStaticMesh.h"
#include "CRenderer.h"
UStaticMesh::UStaticMesh(const TArray<FVertexSimple>& vertices, const TArray<UINT32>& indices)
	: Vertices(vertices), Indices(indices)
{
	//_vertexShader = new VertexShader(device);
	//_vertexShader->Create(L"Shader.hlsl", "VS", "vs_5_0");

	//_pixelShader = new PixelShader(device);
	//_pixelShader->Create(L"Shader.hlsl", "PS", "ps_5_0");

	//_inputLayout = new InputLayout(device);
	//_inputLayout->Create(FVertexSimple::descs, _vertexShader->GetBlob());

	//_constantBuffer = new ConstantBuffer<VS_CB_GAMEOBJECT_INFO>(device, deviceContext);
	//_constantBuffer->Create();

	//_rasterizerState = new RasterizerState(device);
	//_rasterizerState->Create();
}

UStaticMesh::~UStaticMesh()
{
	delete VertexBuffer;
	delete IndexBuffer;
}

void UStaticMesh::CreateBuffer()
{
	ID3D11Device* device = CRenderer::Instance()->GetGraphics()->GetDevice();
	VertexBuffer = new CVertexBuffer<FVertexSimple>(device);
	VertexBuffer->Create(Vertices);
	IndexBuffer = new CIndexBuffer(device);
	IndexBuffer->Create(Indices);
}

CVertexBuffer<FVertexSimple>* UStaticMesh::GetVertexBuffer() const
{
	return VertexBuffer;
}

CIndexBuffer* UStaticMesh::GetIndexBuffer() const
{
	return IndexBuffer;
}