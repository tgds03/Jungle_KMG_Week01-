#include "stdafx.h"
#include "GuiController.h"
#include "Framework/DirectXWrapper/CGraphics.h"
#include "Framework/Core/CEngineStatics.h"
#include "Framework/Core/Time.h"
#include "UWorld.h"

extern UArrowComponent* gAxisXComp;
extern UArrowComponent* gAxisYComp;
extern UArrowComponent* gAxisZComp;

GuiController::GuiController(HWND hWnd, CGraphics* graphics): hWnd(hWnd) {
	IMGUI_CHECKVERSION();
	_context = ImGui::CreateContext();
	_io = &ImGui::GetIO();
	//_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplDX11_Init(graphics->GetDevice(), graphics->GetDeviceContext());
	ImGui_ImplWin32_Init(hWnd);
	_console = new GuiConsole(this);
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
	ImGui::Begin("MousePos");
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(hWnd, &cursorPos);
	ImGui::Text("X : %d, Y : %d", cursorPos.x, cursorPos.y);
	static RECT rect;
	GetClientRect(hWnd, &rect);
	ImGui::Text("Width : %d, Height : %d", rect.right - rect.left, rect.bottom - rect.top);
	ImGui::End();
	//POINT p;
	//GetCursorPos(&p);
	//ScreenToClient(hWnd, &p);
	//_io->MousePos.x = static_cast<float>(p.x);
	//_io->MousePos.y = static_cast<float>(p.y);
	int x, y, w;
	Input::Instance()->GetMouseLocation(x, y);
	Input::Instance()->GetMouseWheel(w);
	_io->MousePos.x = static_cast<float>(x);
	_io->MousePos.y = static_cast<float>(y);
	_io->MouseWheel = static_cast<float>(w);
	_io->MouseDown[0] = Input::Instance()->IsMouseButtonDown(0);
	_io->MouseDown[1] = Input::Instance()->IsMouseButtonDown(1);

	Picking();
}

void GuiController::Picking() {
	if (Input::Instance()->IsMouseButtonPressed(0) && !_io->WantCaptureMouse) {
		int x, y;
		Input::Instance()->GetMouseLocation(x, y);
		_selected = world->PickingByRay(x, y, gAxisXComp, gAxisYComp, gAxisZComp);
	}
		
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

	ImGui::Text("UActorComponent Count: %d", world->GetActorCount());
	
	ImGui::Combo("Primitive", &_selectedPrimitive, primitiveItems, ARRAYSIZE(primitiveItems));
	if ( ImGui::Button("Create") ) {
		for (int i = 0; i < _spawnNumber; i++) {
			switch ( _selectedPrimitive ) {
			case 0:
				_selected = world->SpawnCubeActor();
				break;
			case 1:
				_selected = world->SpawnSphereActor();
				break;
			case 2:
				_selected = world->SpawnPlaneActor();
				break;
			}
			//world->AddActor(_selected);
		}
	}
	ImGui::SameLine(0.f, 5.f);
	ImGui::InputInt("Number of Spawn", &_spawnNumber, 1, 50);
	ImGui::Separator();

	if ( _spawnNumber < 0 ) 
		_spawnNumber = 0;

	ImGui::InputText("Scene Name", _sceneNameBuffer, ARRAYSIZE(_sceneNameBuffer));
	if (ImGui::Button("New Scene")) {
		world->ClearWorld();
		_selected = nullptr;
	}
	if (ImGui::Button("Save Scene")) {
		world->SaveWorld(_sceneNameBuffer);
	}
	if (ImGui::Button("Load Scene")) {
		world->LoadWorld(_sceneNameBuffer);
		_selected = nullptr;
	}

	ImGui::End();

	ImGui::Begin("Property");
	USceneComponent* downcast = nullptr;
	if (_selected)
		downcast = dynamic_cast<USceneComponent*>(_selected);
	if (downcast != nullptr) {
		/*ImGui::SliderFloat3("position", &downcast->RelativeLocation.x, -50.f, 50.f);
		ImGui::SliderFloat3("rotation", &downcast->RelativeRotation.x, -M_PI, M_PI);
		ImGui::SliderFloat3("scale", &downcast->RelativeScale3D.x, -5.f, 5.f);*/
		ImGui::Text("UUID: %d", _selected->GetUUID());
		ImGui::DragFloat3("position", &downcast->RelativeLocation.x, 0.1f);
		ImGui::DragFloat3("rotation", &downcast->RelativeRotation.x, 0.1f);
		ImGui::DragFloat3("scale", &downcast->RelativeScale3D.x, 0.1f);
		if ( ImGui::Button("Delete") ) {
			world->RemoveActor(_selected);
			_selected = nullptr;
		}
	}
	ImGui::End();

	_console->Render();
	//ImGui::ShowDemoWindow();
	//ImGui::ShowDebugLogWindow();
}
