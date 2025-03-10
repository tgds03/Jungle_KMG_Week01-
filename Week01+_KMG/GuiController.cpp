#include "stdafx.h"
#include "GuiController.h"
#include "Framework/DirectXWrapper/CGraphics.h"
#include "Framework/Core/CEngineStatics.h"
#include "Framework/Core/Time.h"
#include "Framework/Core/UCubeComponent.h"
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
	float controllWindowWidth = static_cast<float>(SCR_WIDTH) * 0.3f;
	float controllWindowHeight = static_cast<float>(SCR_HEIGHT) * 0.25f;
	float controllWindowPosX = (static_cast<float>(SCR_WIDTH) - controllWindowWidth) * 0.f;
	float controllWindowPosY = (static_cast<float>(SCR_HEIGHT) - controllWindowHeight) * 0.f;
	ImGui::SetNextWindowPos(ImVec2(controllWindowPosX, controllWindowPosY));
	ImGui::SetNextWindowSize(ImVec2(controllWindowWidth, 0.0f), ImGuiCond_Once);

	// â�� ũ�� ������ �����Ͽ� �ʺ�� �����ϰ� ���̴� �ּ� 0, �ִ� ������(FLT_MAX)���� �����մϴ�.
	ImGui::SetNextWindowSizeConstraints(ImVec2(300.0f, 0.0f), ImVec2(300.0f, FLT_MAX));

	const char* primitiveItems[] = { "Cube", "Sphere", "Plane" };
	ImGui::Begin("Control Panel",nullptr, ImGuiWindowFlags_AlwaysAutoResize);

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
	float propertyWindowWidth = static_cast<float>(SCR_WIDTH) * 0.3f;
	float propertyWindowHeight = static_cast<float>(SCR_HEIGHT) * 0.25f;
	float propertyWindowPosX = (static_cast<float>(SCR_WIDTH) - propertyWindowWidth) * 1.f;
	float propertyWindowPosY = (static_cast<float>(SCR_HEIGHT) - propertyWindowHeight) * 0.f;
	ImGui::SetNextWindowPos(ImVec2(propertyWindowPosX, propertyWindowPosY));
	ImGui::SetNextWindowSize(ImVec2(propertyWindowWidth, 0.0f));
	ImGui::Begin("Property",0);
	USceneComponent* downcast = nullptr;
	if (_selected)
		downcast = dynamic_cast<USceneComponent*>(_selected);
	if (downcast != nullptr) {
		/*ImGui::SliderFloat3("position", &downcast->RelativeLocation.x, -50.f, 50.f);
		ImGui::SliderFloat3("rotation", &downcast->RelativeRotation.x, -M_PI, M_PI);
		ImGui::SliderFloat3("scale", &downcast->RelativeScale3D.x, -5.f, 5.f);*/
		ImGui::Text("UUID: %d", _selected->GetUUID());
		
		
		FVector vec = downcast->GetRelativeLocation();
		float downcastLocation[3] = { vec.x, vec.y, vec.z };
		ImGui::DragFloat3("position", downcastLocation, 0.1f);
		downcast->SetRelativeLocation(FVector(downcastLocation[0], downcastLocation[1], downcastLocation[2]));

		vec = downcast->GetRelativeRotation();
		float downcastRotation[3] = { vec.x, vec.y, vec.z };
		ImGui::DragFloat3("rotation", downcastRotation, 0.1f);
		downcast->SetRelativeRotation(FVector(downcastRotation[0], downcastRotation[1], downcastRotation[2]));

		vec = downcast->GetRelativeScale3D();
		float downcastScale[3] = { vec.x, vec.y, vec.z };
		ImGui::DragFloat3("scale", downcastScale, 0.1f);
		downcast->SetRelativeScale3D(FVector(downcastScale[0], downcastScale[1], downcastScale[2]));

		//ImGui::DragFloat3("rotation", &downcast->RelativeRotation.x, 0.1f);
		//ImGui::DragFloat3("scale", &downcast->RelativeScale3D.x, 0.1f);
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

void GuiController::Resize()
{
	
	
	_io->DisplaySize = ImVec2(static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT));


}

GuiConsole* GuiController::GetConcolWindow()
{
	return _console;
}
