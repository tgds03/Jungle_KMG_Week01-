#pragma once
#include "Framework\DirectXWrapper\CShader.h"
#include "Framework\DirectXWrapper\CInputLayout.h"
#include "Framework\DirectXWrapper\CGraphics.h"
#include "Framework/DirectXWrapper/CState.h"

class CRenderer {
private:
	CRenderer() {};
	CRenderer(const CRenderer& ref) = delete;
	CRenderer& operator=(const CRenderer& ref) = delete;
	~CRenderer() {
		SafeRelease(&_vertexShader);
		SafeRelease(&_pixelShader);
		SafeRelease(&_graphics);
	};
public:
	static CRenderer* Instance() {
		static CRenderer* _instance = new CRenderer();
		return _instance;
	};
	void Init(HWND hWnd);

	CGraphics* GetGraphics() { return _graphics; }
	void SetVertexShader(const FWString filename, FString funcname, FString version);
	void ResetVertexShader();
	void SetPixelShader(const FWString filename, FString funcname, FString version);
	void ResetPixelShader();
	void SetRasterzierState();
private:
	CGraphics* _graphics = nullptr;
	CVertexShader* _vertexShader = nullptr;
	CPixelShader* _pixelShader = nullptr;
	CInputLayout* _inputLayout = nullptr;
	CRasterzierState* _rasterizerState = nullptr;
};

