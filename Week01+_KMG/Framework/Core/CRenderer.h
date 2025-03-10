#pragma once
#include "Framework\DirectXWrapper\CShader.h"
#include "Framework\DirectXWrapper\CInputLayout.h"
#include "Framework\DirectXWrapper\CGraphics.h"
#include "Framework\DirectXWrapper\CState.h"
#include "Framework\DirectXWrapper\CBuffer.h"
#include "./UCameraComponent.h"

class CRenderer {
private:
	static CRenderer* _instance;
	CRenderer();
	CRenderer(const CRenderer& ref) = delete;
	CRenderer& operator=(const CRenderer& ref) = delete;
	~CRenderer() {
		delete _vertexShader;
		_vertexShader = nullptr;
		delete _pixelShader;
		_pixelShader = nullptr;
		delete _inputLayout;
		_inputLayout = nullptr;
		delete _rasterizerState;
		_rasterizerState = nullptr;
		delete _matrixBuffer;
		_matrixBuffer = nullptr;
		delete _flagsBuffer;
		_flagsBuffer = nullptr;
		delete _mainCamera;
		_mainCamera = nullptr;
		delete _graphics;
		_graphics = nullptr;
		
	};
public:
	static CRenderer* Instance() {
		if (_instance == nullptr)
			_instance = new CRenderer();
		return _instance;
	};
	static void Release() {
		delete _instance;
		_instance = nullptr;
	}
	void Init(HWND hWnd);
	

	CGraphics* GetGraphics() { return _graphics; }
	void SetVertexShader(const FWString filename, FString funcname, FString version);
	void ResetVertexShader();
	void SetPixelShader(const FWString filename, FString funcname, FString version);
	void ResetPixelShader();
	void SetRasterzierState();
	void SetTransformToConstantBuffer(FMatrix matrix);
	void SetFlagsToConstantBuffer(FPrimitiveFlags flags);
	UCameraComponent* GetMainCamera() const;
	void SetMainCamera(UCameraComponent* camera);
private:
	CGraphics* _graphics = nullptr;
	CVertexShader* _vertexShader = nullptr;
	CPixelShader* _pixelShader = nullptr;
	CInputLayout* _inputLayout = nullptr;
	CRasterzierState* _rasterizerState = nullptr;
	CConstantBuffer<FMatrix>* _matrixBuffer = nullptr;
	CConstantBuffer<FPrimitiveFlags>* _flagsBuffer = nullptr;
	UCameraComponent* _mainCamera = nullptr;
};

