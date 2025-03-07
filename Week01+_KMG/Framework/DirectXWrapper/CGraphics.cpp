#include "stdafx.h"
#include "CGraphics.h"

CGraphics::CGraphics(HWND hWnd): _hWnd(hWnd) {
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
}

CGraphics::~CGraphics() {
	Release();
}

void CGraphics::RenderBegin() {
	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, nullptr);
	_deviceContext->ClearRenderTargetView(_renderTargetView, _clearColor);
}

void CGraphics::RenderEnd() {
	_swapChain->Present(1, 0);
}

void CGraphics::Release() {
	ReleaseRenderTargetView();
	ReleaseDeviceAndSwapChain();
}

void CGraphics::CreateDeviceAndSwapChain() {
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferDesc.Width = _width;
	desc.BufferDesc.Height = _height;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.OutputWindow = _hWnd;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&desc,
		&_swapChain,
		&_device,
		nullptr,
		&_deviceContext
	);
	assert(SUCCEEDED(hr));
}

void CGraphics::ReleaseDeviceAndSwapChain() {
	if ( _deviceContext )
		_deviceContext->Flush();
	SafeRelease(&_renderTargetView);
	SafeRelease(&_deviceContext);
	SafeRelease(&_device);
}

void CGraphics::CreateRenderTargetView() {
	HRESULT hr;
	
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_backBuffer);
	assert(SUCCEEDED(hr));

	D3D11_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = _device->CreateRenderTargetView(_backBuffer, &desc, &_renderTargetView);
	assert(SUCCEEDED(hr));
}

void CGraphics::ReleaseRenderTargetView() {
	SafeRelease(&_backBuffer);
	SafeRelease(&_renderTargetView);
}
