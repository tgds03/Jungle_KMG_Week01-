#pragma once
#include "Framework\DirectXWrapper\CGraphics.h"
class CRenderer {
private:
	CRenderer() {};
	CRenderer(const CRenderer& ref) = delete;
	CRenderer& operator=(const CRenderer& ref) = delete;
	~CRenderer() {
		SafeRelease(&_graphics);
	};
public:
	static CRenderer* Instance() {
		static CRenderer* _instance = new CRenderer();
		return _instance;
	};
	void Init(HWND hWnd);

	CGraphics* GetGraphics() { return _graphics; }
private:
	CGraphics* _graphics = nullptr;
};

