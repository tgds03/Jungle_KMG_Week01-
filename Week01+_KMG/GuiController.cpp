#include "stdafx.h"
#include "GuiController.h"
#include "Framework/DirectXWrapper/CGraphics.h"
#include "Framework/Core/CEngineStatics.h"
#include "Framework/Core/Time.h"

GuiController::GuiController(HWND hWnd, CGraphics* graphics): hWnd(hWnd) {
	IMGUI_CHECKVERSION();
	_context = ImGui::CreateContext();
	_io = &ImGui::GetIO();
	_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplDX11_Init(graphics->GetDevice(), graphics->GetDeviceContext());
	ImGui_ImplWin32_Init(hWnd);
}

GuiController::~GuiController() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void GuiController::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//POINT p;
	//GetCursorPos(&p);
	//ScreenToClient(hWnd, &p);
	//_io->MousePos.x = static_cast<float>(p.x);
	//_io->MousePos.y = static_cast<float>(p.y);
	int x, y;
	Input::Instance()->GetMouseLocation(x, y);
	_io->MousePos.x = static_cast<float>(x);
	_io->MousePos.y = static_cast<float>(y);
	_io->MouseDown[0] = Input::Instance()->IsMouseButtonDown(0);
	_io->MouseDown[1] = Input::Instance()->IsMouseButtonDown(1);
}

void GuiController::RenderFrame()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void GuiController::RenderEditor() {
	const char* primitiveItems[] = { "Cube", "Sphere", "Plane" };
	ImGui::Begin("Control Panel");

	ImGui::Text("FPS: %.2f (%.2fms)", 1/Time::GetDeltaTime(), 1000.f * Time::GetDeltaTime());
	ImGui::Text("UObject Count: %d", CEngineStatics::TotalAllocationCount);
	ImGui::Text("UObject Bytes: %d", CEngineStatics::TotalAllocationBytes);
	ImGui::Separator();
	
	ImGui::Combo("Primitive", &_selectedPrimitive, primitiveItems, ARRAYSIZE(primitiveItems));
	if ( ImGui::Button("Create") ) {
	}
	ImGui::SameLine(0.f, 5.f);
	ImGui::InputInt("Number of Spawn", &_spawnNumber, 1, 50);
	ImGui::Separator();

	ImGui::InputText("Scene Name", _sceneNameBuffer, ARRAYSIZE(_sceneNameBuffer));
	if (ImGui::Button("New Scene")) {
	}
	if (ImGui::Button("Save Scene")) {
	}
	if (ImGui::Button("Load Scene")) {
	}
	ImGui::Separator();



	ImGui::End();
}
