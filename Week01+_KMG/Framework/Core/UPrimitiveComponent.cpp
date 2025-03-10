#include "stdafx.h"
#include "UPrimitiveComponent.h"
#include "./Framework/Core/CRenderer.h"

UPrimitiveComponent::~UPrimitiveComponent() {
	if (_vertexBuffer != nullptr)
		delete _vertexBuffer;
	if ( _indexBuffer != nullptr )
		delete _indexBuffer;
}

void UPrimitiveComponent::Render() {
	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	ID3D11Buffer* vertexBuffer = _vertexBuffer->Get();
	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	graphics->GetDeviceContext()->IASetIndexBuffer(_indexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);
	FMatrix m = GetComponentTransform();
	CRenderer::Instance()->SetTransformToConstantBuffer(m);
	CRenderer::Instance()->SetFlagsToConstantBuffer({ renderFlags });
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
	//카메라 좌표계의 원점을 모델 좌표계로 변환한다. 
	*pickRayOrigin = xmf4x4Inverse.TransformCoord(xmf3CameraOrigin);
	//카메라 좌표계의 점(마우스 좌표를 역변환하여 구한 점)을 모델 좌표계로 변환한다. 
	*rayDirection = xmf4x4Inverse.TransformCoord(pickPosition);
	//광선의 방향 벡터를 구한다. 
	*rayDirection = (*rayDirection - *pickRayOrigin).Normalized();
}

bool UPrimitiveComponent::PickObjectByRayIntersection(const FVector& pickPosition, const FMatrix& viewMatrix, float* hitDistance)
{

		FVector pickRayOrigin, pickRayDirection;
		GenerateRayForPicking(pickPosition, viewMatrix, &pickRayOrigin, &pickRayDirection);

		bool bHit = IntersectsRay(pickRayOrigin, pickRayDirection, *hitDistance);

		if (bHit)
		{
			OutputDebugString(L"Res :: hit!!!!-----------------\n");
		}
		else
		{
			//OutputDebugString(L"Res :: NOT!!!!-----------------\n");
			//OutputDebugString(L"Ray did not hit the cube\n");
		}
		return bHit;
}
