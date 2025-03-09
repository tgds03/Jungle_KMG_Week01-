#include "stdafx.h"
#include "UPrimitiveComponent.h"
#include "./Framework/Core/CRenderer.h"

void UPrimitiveComponent::Render() {
	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	ID3D11Buffer* vertexBuffer = _vertexBuffer->Get();
	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	graphics->GetDeviceContext()->IASetIndexBuffer(_indexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);
	FMatrix m = GetComponentTransform();
	CRenderer::Instance()->SetConstantBuffer(m);
	if (indices.size() > 0)
		graphics->GetDeviceContext()->DrawIndexed(indices.size(), 0, 0);
	else
		graphics->GetDeviceContext()->Draw(vertices.size(), 0);
}


void UPrimitiveComponent::GenerateRayForPicking(const FVector& pickPosition, const FMatrix& viewMatrix, FVector* pickRayOrigin, FVector* rayDirection)
{
	FMatrix xmf4x4WorldView = GetComponentTransform() * viewMatrix;
	FMatrix xmf4x4Inverse = xmf4x4WorldView.Inverse();
	FVector xmf3CameraOrigin(0.0f, 0.0f, 0.0f);
	//ī�޶� ��ǥ���� ������ �� ��ǥ��� ��ȯ�Ѵ�. 
	*pickRayOrigin = xmf4x4Inverse.TransformCoord(xmf3CameraOrigin);
	//ī�޶� ��ǥ���� ��(���콺 ��ǥ�� ����ȯ�Ͽ� ���� ��)�� �� ��ǥ��� ��ȯ�Ѵ�. 
	*rayDirection = xmf4x4Inverse.TransformCoord(pickPosition);
	//������ ���� ���͸� ���Ѵ�. 
	*rayDirection = (*rayDirection - *pickRayOrigin).Normalized();
}
