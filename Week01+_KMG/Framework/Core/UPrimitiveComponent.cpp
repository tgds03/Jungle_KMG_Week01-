#include "stdafx.h"
#include "UPrimitiveComponent.h"

void UPrimitiveComponent::Update()
{
}

void UPrimitiveComponent::Render()
{
	//if (bVisible)
	//{
	//	return;
	//	if (context == nullptr)
	//		return;

	//	context->IASetInputLayout(_inputLayout->Get());
	//	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	context->VSSetShader(_vertexShader->Get(), nullptr, 0);
	//	context->RSSetState(_rasterizerState->Get());
	//	context->PSSetShader(_pixelShader->Get(), nullptr, 0);

	//	UINT32 stride, offset;
	//	ID3D11Buffer* vertexBuffer = _vertexBuffer->Get();
	//	stride = _vertexBuffer->GetStride();
	//	offset = _vertexBuffer->GetOffset();
	//	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//	context->IASetIndexBuffer(_indexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);

	//	_constantBuffer->CopyData(VS_CB_GAMEOBJECT_INFO{ _tf.GetWorldMatrix() });
	//	ID3D11Buffer* constantBuffer = _constantBuffer->Get();
	//	context->VSSetConstantBuffers(2, 1, &constantBuffer);

	//	context->DrawIndexed(_indexBuffer->GetCount(), 0, 0);
	//}
}

void UPrimitiveComponent::setVisible(const bool bValue)
{
	bVisible = bValue;
}
