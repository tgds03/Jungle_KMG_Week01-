#include "stdafx.h"
#include "Framework/Core/CRenderer.h"
#include "Math\FVector.h"
#include "Math\FMatrix.h"
#include "UCubeComponent.h"

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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		nullptr, nullptr, hInstance, nullptr
	);

	CRenderer::Instance()->Init(hWnd); // maincamera ¼³Á¤
	Time::Instance()->Init();
	Input::Instance()->Init(hInstance, hWnd, 800, 600);
	UCubeComponent* obj = new UCubeComponent();
	UCubeComponent* stick = new UCubeComponent();

	USceneComponent* world = new USceneComponent();

	USceneComponent* cam = CRenderer::Instance()->GetCamera();

	cam->AttachToComponent(world);
	obj->AttachToComponent(world);
	stick->AttachToComponent(cam);
	stick->SetRelativeLocation({0, 0, -10});

	//std::vector<USceneComponent*> u;
	//for (int i = 0; i < 6; i++)
	//{
	//	u.push_back(new USceneComponent);
	//}

	//std::vector<USceneComponent*> childs;
	//childs.push_back(u[1]);
	//u[0]->SetupAttachment(childs);


	//u[1]->AttachToComponent(u[0]);
	//u[2]->AttachToComponent(u[1]);
	//u[3]->AttachToComponent(u[1]);
	//u[4]->AttachToComponent(u[3]);
	//u[5]->AttachToComponent(u[3]);


	//u[5]->SetRelativeLocation({ 2000, 2000, 2000 });
	//u[0]->SetRelativeLocation({ 1,1,1 });
	//u[1]->SetRelativeLocation({ 10,10,10 });
	//u[4]->SetRelativeLocation({ 1000,1000,1000 });
	//u[2]->SetRelativeLocation({ 100,100,100 });
	//u[3]->SetRelativeLocation({ 200,200,200 });

	////u[1]->SetRelativeScale3D({ 2,2,2 });

	//u[1]->SetRelativeScale3D({ 2,2,2 });

	//for (int i = 0; i < 6; i++)
	//{
	//	//u[i]->PrintLoc(std::wstring());
	//	u[i]->PrintLoc(std::wstring(L"u[") + std::to_wstring(i) + std::wstring(L"]"));
	//	//comp->Update();
	//}

	//obj->AttachToComponent(CRenderer::Instance()->GetCamera());

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		Time::Instance()->_query_frame_update_time();
		Input::Instance()->Frame();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UActorComponent::UpdateAll();
		CRenderer::Instance()->GetGraphics()->RenderBegin();
		obj->PrintLoc(L"OBJ");
		stick->PrintLoc(L"stick");
		CRenderer::Instance()->GetCamera()->PrintLoc(L"CAM");
		UActorComponent::RenderAll();
		CRenderer::Instance()->GetGraphics()->RenderEnd();
		Time::Instance()->_query_frame_end_time();
		/*do {
			Sleep(0);
			Time::Instance()->_query_frame_end_time();
		} while ( Time::GetDeltaTime() < TARGET_FRAMERATE );*/
		
	}
	Input::Instance()->Shutdown();
	CRenderer::Release();
	return 0;
}