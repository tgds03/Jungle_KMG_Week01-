#include "stdafx.h"
#include "UPrimitiveComponent.h"
#include "CRenderer.h"

UPrimitiveComponent::UPrimitiveComponent() {}

void UPrimitiveComponent::Init(CVertexShader* vertexShader, CPixelShader* pixelShader, UStaticMesh* mesh)
{
	ID3D11Device* device = CRenderer::Instance()->GetGraphics()->GetDevice();
	ID3D11DeviceContext* deviceContext = CRenderer::Instance()->GetGraphics()->GetDeviceContext();

	VertexShader = vertexShader;
	PixelShader = pixelShader;
	Mesh = mesh;

	//VertexShader = new CVertexShader(device);
	//VertexShader->Create(L"Shader.hlsl", "VS", "vs_5_0");

	//PixelShader = new CPixelShader(device);
	//PixelShader->Create(L"Shader.hlsl", "PS", "ps_5_0");

	inputLayout = new InputLayout(device);
	inputLayout->Create(FVertexSimple::descs, VertexShader->GetBlob());

	ConstantBuffer = new CConstantBuffer<FMatrix>(device, deviceContext);
	ConstantBuffer->Create();

	RasterizerState = new CRasterizerState(device);
	RasterizerState->Create();


}

void UPrimitiveComponent::Update()
{
}

void UPrimitiveComponent::Render()
{
	
	if (!bVisible)
	{
		return;
	}
	ID3D11Device* device = CRenderer::Instance()->GetGraphics()->GetDevice();
	ID3D11DeviceContext* deviceContext = CRenderer::Instance()->GetGraphics()->GetDeviceContext();

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetInputLayout(inputLayout->Get());
	deviceContext->VSSetShader(VertexShader->Get(), nullptr, 0);
	deviceContext->RSSetState(RasterizerState->Get());
	deviceContext->PSSetShader(PixelShader->Get(), nullptr, 0);

	UINT32 stride, offset;
	ID3D11Buffer* vertexBuffer = Mesh->GetVertexBuffer()->Get();
	stride = Mesh->GetVertexBuffer()->GetStride();
	offset = Mesh->GetVertexBuffer()->GetOffset();
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(Mesh->GetIndexBuffer()->Get(), DXGI_FORMAT_R32_UINT, 0);

	//ConstantBuffer->CopyData(FMatrix{ GetComponentTransform()});
	//ID3D11Buffer* constantBuffer = ConstantBuffer->Get();
	//deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

	deviceContext->DrawIndexed(Mesh->GetIndexBuffer()->GetCount(), 0, 0);
}

void UPrimitiveComponent::setVisible(const bool bValue)
{
	bVisible = bValue;
}
