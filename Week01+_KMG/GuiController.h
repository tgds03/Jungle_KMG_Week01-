#pragma once
class CGraphics;
class UWorld;

class GuiController {
public:
	GuiController(HWND hWnd, CGraphics* graphics);
	~GuiController();

	void NewFrame();
	void RenderFrame();
	void RenderEditor();
private:
	ImGuiContext* _context;
	ImGuiIO* _io;
	HWND hWnd;
	UWorld* _world;

	char _sceneNameBuffer[256] = "";
	int _selectedPrimitive = 0, _spawnNumber = 0;
};

