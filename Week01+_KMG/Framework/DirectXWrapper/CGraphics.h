#pragma once
class CGraphics {
public:
	CGraphics(HWND hWnd);
	~CGraphics();

	void RenderBegin();
	void RenderEnd();
	void Release();

	ID3D11Device* GetDevice() { return _device; }
	ID3D11DeviceContext* GetDeviceContext() { return _deviceContext; }

private:
	HWND _hWnd;
	uint32 _width = 800;
	uint32 _height = 600;

	ID3D11Device* _device = nullptr;
	ID3D11DeviceContext* _deviceContext = nullptr;
	IDXGISwapChain* _swapChain = nullptr;

	ID3D11Texture2D* _backBuffer = nullptr;
	ID3D11RenderTargetView* _renderTargetView = nullptr;

	float _clearColor[4] = { 1.f, 0.f, 0.f, 1.f };

private:
	void CreateDeviceAndSwapChain();
	void ReleaseDeviceAndSwapChain();
	void CreateRenderTargetView();
	void ReleaseRenderTargetView();
};

