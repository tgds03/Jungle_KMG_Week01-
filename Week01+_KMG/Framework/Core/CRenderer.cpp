#include "stdafx.h"
#include "CRenderer.h"

CRenderer* CRenderer::_instance = nullptr;

CRenderer::CRenderer() {
	_mainCamera = new UCameraComponent();
	_mainCamera->SetRelativeLocation({ 0,0,5.f });

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
	FMatrix view = matrix * _mainCamera->GetRelativeTransform().Inverse();
	FMatrix projection = view * _mainCamera->PerspectiveProjection();
	_constantBuffer->CopyData(projection);
	ID3D11Buffer* constantBuffer = _constantBuffer->Get();
	_graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &constantBuffer);
}

UCameraComponent* CRenderer::GetCamera() const
{
	return _mainCamera;
}

void CRenderer::PickingByRay(LPARAM lParam)
{
	FMatrix view = _mainCamera->GetComponentTransform().Inverse();
	FMatrix proj = _mainCamera->PerspectiveProjection();
	D3D11_VIEWPORT viewport = _graphics->GetViewport();

	FVector pickPosition;
	float size_x = LOWORD(lParam);
	float size_y = HIWORD(lParam);
	pickPosition.x = (((2.0f * size_x) / viewport.Width) - 1) / proj[1][1];
	pickPosition.y = -(((2.0f * size_y) / viewport.Height) - 1) / proj[2][2];
	pickPosition.z = 1;

	UActorComponent::GenerateAllRayForPicking(pickPosition, view);

}