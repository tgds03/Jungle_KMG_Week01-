#include "stdafx.h"
#include "CRenderer.h"

void CRenderer::Init(HWND hWnd) {
	_graphics = new CGraphics(hWnd);
}
