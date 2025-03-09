#pragma once
#include "GuiConsole.h"

class CGraphics;
class UActorComponent;
class UWorld;

class GuiController {
public:
	GuiController(HWND hWnd, CGraphics* graphics);
	~GuiController();

	void NewFrame();
	void RenderFrame();
	void RenderEditor();

	UWorld* world;
	UActorComponent* _selected;
private:
	ImGuiContext* _context;
	ImGuiIO* _io;
	HWND hWnd;
	GuiConsole* _console;

	char _sceneNameBuffer[256] = "";
	int _selectedPrimitive = 0, _spawnNumber = 1;
};

