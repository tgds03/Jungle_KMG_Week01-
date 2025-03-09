#include "stdafx.h"
#include "CRenderer.h"

CRenderer* CRenderer::_instance = nullptr;

CRenderer::CRenderer() {
	_mainCamera = new UCameraComponent();
	//_mainCamera->SetRelativeLocation({ 0,0,5.f });

	//_mainCamera->GetRelativeLocation().z = 5.f;
}

void CRenderer::Init(HWND hWnd) {
	_graphics = new CGraphics(hWnd);
	_constantBuffer = new CConstantBuffer<FMatrix>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_constantBuffer->Create();
	SetVertexShader(L"Shader.hlsl", "VS", "vs_5_0");
	SetPixelShader(L"Shader.hlsl", "PS", "ps_5_0");
	SetRasterzierState();
	_graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void CRenderer::SetVertexShader(const FWString filename, FString funcname, FString version) {
	if ( _graphics == nullptr )
		assert(0);
	if ( _vertexShader != nullptr )
		ResetVertexShader();
	if ( _inputLayout != nullptr )
		SafeRelease(&_inputLayout);

	_vertexShader = new CVertexShader(_graphics->GetDevice());
	_vertexShader->Create(filename, funcname, version);

	_inputLayout = new CInputLayout(_graphics->GetDevice());
	_inputLayout->Create(FVertexSimple::descs, _vertexShader->GetBlob());

	_graphics->GetDeviceContext()->IASetInputLayout(_inputLayout->Get());
	_graphics->GetDeviceContext()->VSSetShader(_vertexShader->Get(), nullptr, 0);
	
}

void CRenderer::ResetVertexShader() {
	_graphics->GetDeviceContext()->VSSetShader(nullptr, nullptr, 0);
	SafeRelease(&_vertexShader);
}

void CRenderer::SetPixelShader(const FWString filename, FString funcname, FString version) {
	if ( _graphics == nullptr )
		assert(0);
	if ( _pixelShader != nullptr )
		ResetPixelShader();
	_pixelShader = new CPixelShader(_graphics->GetDevice());
	_pixelShader->Create(filename, funcname, version);
	_graphics->GetDeviceContext()->PSSetShader(_pixelShader->Get(), nullptr, 0);
}

void CRenderer::ResetPixelShader() {
	_graphics->GetDeviceContext()->PSSetShader(nullptr, nullptr, 0);
	SafeRelease(&_vertexShader);
}

void CRenderer::SetRasterzierState() {
	_rasterizerState = new CRasterzierState(_graphics->GetDevice());
	_rasterizerState->Create();
	_graphics->GetDeviceContext()->RSSetState(_rasterizerState->Get());
}

void CRenderer::SetConstantBuffer(FMatrix matrix) {
	//FMatrix view = matrix * _mainCamera->GetRelativeTransform().Inverse();
	FMatrix view = _mainCamera->View();
	FMatrix projection = _mainCamera->PerspectiveProjection();
	matrix = matrix * view;
	matrix = matrix * projection;
	_constantBuffer->CopyData(matrix);
	ID3D11Buffer* constantBuffer = _constantBuffer->Get();
	_graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &constantBuffer);
}

UCameraComponent* CRenderer::GetCamera() const
{
	return _mainCamera;
}

void CRenderer::PickingByRay(LPARAM lParam)
{
	
	FMatrix viewMatrix = _mainCamera->GetComponentTransform().Inverse();
	FMatrix projectionMatrix = _mainCamera->PerspectiveProjection();
	D3D11_VIEWPORT viewport = _graphics->GetViewport();

	
	float size_x = LOWORD(lParam);
	float size_y = HIWORD(lParam);

	FVector ndcPosition;
	ndcPosition.x = (2.0f * size_x / viewport.Width) - 1.0f;
	ndcPosition.y = 1.0f - (2.0f * size_y / viewport.Height); // DX11은 Y축 반전 없음
	ndcPosition.z = 1.0f; // Near Plane

	
	FVector nearPoint = FVector(ndcPosition.x, ndcPosition.y, 0.0f); // Near Plane
	FVector farPoint = FVector(ndcPosition.x, ndcPosition.y, 1.0f);  // Far Plane

	
	FMatrix invProjMatrix = projectionMatrix.Inverse();
	FVector nearPointView = invProjMatrix.TransformCoord(FVector4(nearPoint, 1.0f));
	FVector farPointView = invProjMatrix.TransformCoord(FVector4(farPoint, 1.0f));



	FMatrix invViewMatrix = viewMatrix.Inverse();
	FVector nearPointWorld = invViewMatrix.TransformCoord(FVector4(nearPointView, 1.0f));
	FVector farPointWorld = invViewMatrix.TransformCoord(FVector4(farPointView, 1.0f));

	
	FVector rayOrigin = nearPointWorld; //
	FVector rayDirection = (farPointWorld - nearPointWorld).Normalized(); // Ray 방향

	// 디버깅 출력
	OutputDebugString((L"Ray Origin (World): x=" + std::to_wstring(rayOrigin.x) +
		L", y=" + std::to_wstring(rayOrigin.y) +
		L", z=" + std::to_wstring(rayOrigin.z) + L"\n").c_str());

	OutputDebugString((L"Ray Direction (World): x=" + std::to_wstring(rayDirection.x) +
		L", y=" + std::to_wstring(rayDirection.y) +
		L", z=" + std::to_wstring(rayDirection.z) + L"\n").c_str());

	
	UActorComponent::GenerateAllRayForPicking(rayOrigin, rayDirection,viewMatrix);
}
