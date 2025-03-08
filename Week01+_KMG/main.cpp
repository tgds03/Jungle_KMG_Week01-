#include "stdafx.h"
#include "Framework/Core/CRenderer.h"
#include "Math\FVector.h"
#include "Math\FMatrix.h"
#include "Framework/Core/UCubeComponent.h"
#include "UWorld.h"
#include "Framework/Core/UPlaneComponent.h"
#include "Framework/Core/UCoordArrowComponent.h"

const int TARGET_FPS = 60;
const double TARGET_FRAMERATE = 1000.0 / TARGET_FPS;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
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

	HWND hWnd = CreateWindow(winClassName, winTitleName,
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SCR_WIDTH, SCR_HEIGHT,
		nullptr, nullptr, hInstance, nullptr
	);

	CRenderer::Instance()->Init(hWnd); // maincamera ����
	Time::Instance()->Init();
	Input::Instance()->Init(hInstance, hWnd, 800, 600);

	GuiController* guiController = new GuiController(hWnd, CRenderer::Instance()->GetGraphics());

	UWorld* mainScene = new UWorld();

	UPlaneComponent* ground = mainScene->SpawnPlaneActor();
	UCubeComponent* obj = mainScene->SpawnCubeActor();
	UCoordArrowComponent* arrow = mainScene->SpawnCoordArrowActor();
	UCoordArrowComponent* worldArrow = mainScene->SpawnCoordArrowActor();

	CRenderer::Instance()->GetCamera()->SetRelativeLocation(FVector(0, 0, -5));

	worldArrow->SetRelativeScale3D({ 100,100,100 });
	ground->SetRelativeScale3D({ 10,5,3 });
	//ground->SetRelativeLocation({ 0,-10,0 });
	arrow->SetRelativeScale3D({ 3,3,3 });

	arrow->SetRelativeLocation({ 0,0,0 });
	arrow->AttachToComponent(obj);
	obj->SetRelativeRotation({ 0,1,0 });

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		Time::Instance()->_query_frame_update_time();
		Input::Instance()->Frame();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		////////////////////////////////
		// CUBE - ARROW 따라가는지 테스트용

		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_J))
		{
			obj->SetRelativeLocation(obj->GetRelativeLocation() - obj->Right());
		}
		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_L))
		{
			obj->SetRelativeLocation(obj->GetRelativeLocation() + obj->Right());
		}
		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_I))
		{
			obj->SetRelativeLocation(obj->GetRelativeLocation() + obj->Front());
		}
		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_K))
		{
			obj->SetRelativeLocation(obj->GetRelativeLocation() - obj->Front());
		}
		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_O))
		{
			obj->SetRelativeLocation(obj->GetRelativeLocation() + obj->Up());
		}
		if (Input::Instance()->IsKeyPressed(DIKEYBOARD_U))
		{
			obj->SetRelativeLocation(obj->GetRelativeLocation() - obj->Up());
		}
		CRenderer::Instance()->GetCamera()->PrintLoc(L"CAM");
		obj->PrintLoc(L"obj");
		
		// 테스트용
		////////////////////////////////
		
		mainScene->Update();
		CRenderer::Instance()->GetGraphics()->RenderBegin();
		guiController->NewFrame();
		mainScene->Render();
		guiController->RenderFrame();
		CRenderer::Instance()->GetGraphics()->RenderEnd();
		Time::Instance()->_query_frame_end_time();
		
	}
	Input::Instance()->Shutdown();
	CRenderer::Release();
	return 0;
}