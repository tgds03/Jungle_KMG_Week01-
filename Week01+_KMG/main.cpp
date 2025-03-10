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
#include "Framework/Core/UDiscHollowComponent.h"
extern int SCR_WIDTH;
extern int SCR_HEIGHT;
const int TARGET_FPS = 60;
const double TARGET_FRAMERATE = 1000.0 / TARGET_FPS;

UWorld* gMainScene;
UArrowComponent* gAxisXComp;
UArrowComponent* gAxisYComp;
UArrowComponent* gAxisZComp;
UGizmoComponent* gGizmo;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		if(gMainScene)
		{
			gMainScene->PickingByRay(LOWORD(lParam), HIWORD(lParam), gAxisXComp, gAxisYComp, gAxisZComp);
			auto cam = CRenderer::Instance()->GetMainCamera();
			Input::Instance()->SpawnMouseRay(cam->View(), cam->PerspectiveProjection());
		}
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

	UWorld* mainScene = new UWorld();
	gMainScene = mainScene;
	//UPlaneComponent* ground = mainScene->SpawnPlaneActor();
	UCubeComponent* obj = mainScene->SpawnCubeActor();
	UCubeComponent* obj2 = mainScene->SpawnCubeActor();
	//USphereComponent* sphere = mainScene->SpawnSphereACtor();
	UCoordArrowComponent* arrow = mainScene->SpawnCoordArrowActor();
	UCoordArrowComponent* worldArrow = mainScene->SpawnCoordArrowActor();
	//USphereComponent* sphere = mainScene->SpawnSphereACtor();
	//UDiscComponent* disc = mainScene->SpawnDiscActor();
	//UDiscHollowComponent* disc = new UDiscHollowComponent(RED_X, 0.9f);
	UDiscHollowComponent* disc = mainScene->SpawnDiscHollowActor();
	
	//disc->SetRelativeRotation({ 10,10,10 });
	//sphere->SetRelativeScale3D({ 1,1,1 });
	//sphere->SetRelativeRotation({ 1,2,3 });

	UArrowComponent* AxisXComp = new UArrowComponent(RED_X);
	UArrowComponent* AxisYComp = new UArrowComponent(GREEN_Y);
	UArrowComponent* AxisZComp = new UArrowComponent(BLUE_Z);
	UGizmoComponent* Gizmo = new UGizmoComponent(AxisXComp, AxisYComp, AxisZComp);
	UCoordArrowComponent* c = new UCoordArrowComponent();
	c->AttachToComponent(disc);
	//disc->SetRelativeRotationX(1.0);
	Gizmo->AttachToComponent(obj2);
	AxisXComp->SetRelativeRotation({ 0,-M_PI/2,0 });
	AxisYComp->SetRelativeRotation({ M_PI / 2 ,0,0});
	AxisZComp->SetRelativeRotation({ 0,0,0 });

	AxisXComp->SetRelativeScale3D({ 0.8, 0.8 ,0.8 });
	AxisYComp->SetRelativeScale3D({ 0.8, 0.8 ,0.8 });
	AxisZComp->SetRelativeScale3D({ 0.8, 0.8 ,0.8 });


	CRenderer::Instance()->GetMainCamera()->SetRelativeLocation(FVector(0, 0, -5));

	gAxisXComp = AxisXComp;
	gAxisYComp = AxisYComp;
	gAxisZComp = AxisZComp;
	gGizmo = Gizmo;

	worldArrow->SetRelativeScale3D({ 100,100,100 });
	//ground->SetRelativeScale3D({ 10,5,3 });
	//ground->SetRelativeLocation({ 0,-10,0 });
	arrow->SetRelativeScale3D({ 3,3,3 });

	arrow->SetRelativeLocation({ 0,0,0 });
	arrow->AttachToComponent(obj);
	obj->SetRelativeLocation({ 10,1,1 });
	obj2->SetRelativeLocation({ 0,0,10 });

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
		//CRenderer::Instance()->GetCamera()->PrintLoc(L"CAM");
		//obj->PrintLoc(L"obj");

		// 테스트용
		////////////////////////////////
		//Input::Instance()->Frame();
		guiController->NewFrame();
		mainScene->Update();
		CRenderer::Instance()->GetGraphics()->RenderBegin();
		gGizmo->Update();
		disc->Render();
		c->Render();
		obj2->SetRelativeRotation(obj2->GetRelativeRotation() + FVector{0.1, 0.2, 0.3});
		gGizmo->Render();
		mainScene->Render();
		AxisXComp->Render();
		AxisYComp->Render();
		AxisZComp->Render();
		ImGui::ShowDebugLogWindow();
		ImGui::Begin("statics");
		ImGui::Text("UObject Count: %d", CEngineStatics::TotalAllocationCount);
		ImGui::Text("UObject Bytes: %d", CEngineStatics::TotalAllocationBytes);
		ImGui::End();

		guiController->RenderFrame();
		CRenderer::Instance()->GetGraphics()->RenderEnd();
		Time::Instance()->_query_frame_end_time();
		
	}
	Input::Instance()->Shutdown();
	CRenderer::Release();
	return 0;
}