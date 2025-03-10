#include "stdafx.h"
#include "Framework/Core/CRenderer.h"
#include "Math\FVector.h"
#include "Math\FMatrix.h"
#include "Framework/Core/UCubeComponent.h"
#include "UWorld.h"
#include "Framework/Core/UPlaneComponent.h"
#include "Framework/Core/UCoordArrowComponent.h"
#include "Framework/Core/UArrowComponent.h"
#include "Framework/Core/UGizmoComponent.h"
extern int SCR_WIDTH;
extern int SCR_HEIGHT;
const int TARGET_FPS = 60;
const double TARGET_FRAMERATE = 1000.0 / TARGET_FPS;

UWorld* gMainScene;
UArrowComponent* gAxisXComp;
UArrowComponent* gAxisYComp;
UArrowComponent* gAxisZComp;
UGizmoComponent* gGizmo;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if ( ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam) )
		return true;
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		if(gMainScene)
			gMainScene->PickingByRay(LOWORD(lParam), HIWORD(lParam), gAxisXComp, gAxisYComp, gAxisZComp);
		break;
	//case WM_SIZE:
	//{
	//	//if (CRenderer::Instance()->GetGraphics() && CRenderer::Instance()->GetGraphics()->GetDevice() && CRenderer::Instance()->GetGraphics()->GetDeviceContext()) {
	//		//SCR_WIDTH = LOWORD(lParam);
	//		//SCR_HEIGHT = HIWORD(lParam);
	//		//CRenderer::Instance()->GetGraphics()->ResizeBuffers(SCR_WIDTH, SCR_HEIGHT);
	//	}
	//}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WCHAR winClassName[] = L"WindowClass";
	WCHAR winTitleName[] = L"Title";

	WNDCLASS winClass = {};
	winClass.hInstance = hInstance;
	winClass.lpszClassName = winClassName;
	winClass.lpfnWndProc = WinProc;
	RegisterClass(&winClass);



	RECT rc = { 0, 0, SCR_WIDTH, SCR_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindow(winClassName, winTitleName,
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		nullptr, nullptr, hInstance, nullptr
	);

	CRenderer::Instance()->Init(hWnd); // maincamera ����
	Time::Instance()->Init();
	Input::Instance()->Init(hInstance, hWnd, SCR_WIDTH, SCR_HEIGHT);

	GuiController* guiController = new GuiController(hWnd, CRenderer::Instance()->GetGraphics());
	guiController->world = new UWorld();


	UArrowComponent* AxisXComp = new UArrowComponent(EAxisColor::RED_X);
	UArrowComponent* AxisYComp = new UArrowComponent(EAxisColor::GREEN_Y);
	UArrowComponent* AxisZComp = new UArrowComponent(EAxisColor::BLUE_Z);
	UGizmoComponent* Gizmo = new UGizmoComponent(AxisXComp, AxisYComp, AxisZComp);

	//Gizmo->AttachToComponent(sphere);
	AxisXComp->SetRelativeRotation({ 0,-M_PI/2,0 });
	AxisYComp->SetRelativeRotation({ M_PI / 2 ,0,0});
	AxisZComp->SetRelativeRotation({ 0,0,0 });
	CRenderer::Instance()->GetMainCamera()->SetRelativeLocation(FVector(0, 0, -5));

	gAxisXComp = AxisXComp;
	gAxisYComp = AxisYComp;
	gAxisZComp = AxisZComp;
	gGizmo = Gizmo;

	//FString jsonOutput = DataManager::Instance().GenerateWorldJson(mainScene);


	MSG msg = {};
	while (msg.message != WM_QUIT) {
		Time::Instance()->_query_frame_update_time();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		////////////////////////////////
		// CUBE - ARROW 따라가는지 
		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_N))
		{
			guiController->world->SaveWorld("TestLevel");
			//mainScene->RemoveActor(sphere);
		}

		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_M))
		{
			guiController->world->LoadWorld("TestLevel");
		}


		//if (Input::Instance()->IsKeyPressed(DIKEYBOARD_J))
		//{
		//	obj->SetRelativeLocation(obj->GetRelativeLocation() - obj->Right());
		//}
		//if (Input::Instance()->IsKeyPressed(DIKEYBOARD_L))
		//{
		//	obj->SetRelativeLocation(obj->GetRelativeLocation() + obj->Right());
		//}
		//if (Input::Instance()->IsKeyPressed(DIKEYBOARD_I))
		//{
		//	obj->SetRelativeLocation(obj->GetRelativeLocation() + obj->Front());
		//}
		//if (Input::Instance()->IsKeyPressed(DIKEYBOARD_K))
		//{
		//	obj->SetRelativeLocation(obj->GetRelativeLocation() - obj->Front());
		//}
		//if (Input::Instance()->IsKeyPressed(DIKEYBOARD_O))
		//{
		//	obj->SetRelativeLocation(obj->GetRelativeLocation() + obj->Up());
		//}
		//if (Input::Instance()->IsKeyPressed(DIKEYBOARD_U))
		//{
		//	obj->SetRelativeLocation(obj->GetRelativeLocation() - obj->Up());
		//}
		//CRenderer::Instance()->GetCamera()->PrintLoc(L"CAM");
		//obj->PrintLoc(L"obj");

		// 테스트용
		////////////////////////////////
		//Input::Instance()->Frame();
		Input::Instance()->Frame();
		//Input::Instance()->Unacquire();
		guiController->NewFrame();
		guiController->world->Update();
		CRenderer::Instance()->GetGraphics()->RenderBegin();
		guiController->world->Render();
		AxisXComp->Render();
		AxisYComp->Render();
		AxisZComp->Render();
		guiController->RenderEditor();
		guiController->RenderFrame();
		CRenderer::Instance()->GetGraphics()->RenderEnd();
		Time::Instance()->_query_frame_end_time();
		//if (!SUCCEEDED(Input::Instance()->Acquire()))
		//	assert(0);
		
	}
	Input::Instance()->Shutdown();
	CRenderer::Release();
	return 0;
}