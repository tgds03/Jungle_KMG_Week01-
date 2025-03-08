#pragma once
class CGraphics;
class GuiController {
public:
	GuiController(HWND hWnd, CGraphics* graphics);
	~GuiController();

	void NewFrame();
	void RenderFrame();
private:
	ImGuiContext* _context;
	ImGuiIO* _io;
	HWND hWnd;
};

