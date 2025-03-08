#include "stdafx.h"
#include "Framework/Core/CRenderer.h"
#include "Math\FVector.h"
#include "Math\FMatrix.h"
#include "Framework/Core/AActor.h"
#include "Framework/Core/UCubeComp.h"

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


	std::vector<USceneComponent*> u;

	for (int i = 0; i < 6; i++)
	{
		u.push_back(new USceneComponent);
	}

	//std::vector<USceneComponent*> childs;
	//childs.push_back(u[1]);
	//u[0]->SetupAttachment(childs);

	u[1]->AttachToComponent(u[0]);
	u[2]->AttachToComponent(u[1]);
	u[3]->AttachToComponent(u[1]);
	u[4]->AttachToComponent(u[3]);
	u[5]->AttachToComponent(u[3]);


	u[5]->SetRelativeLocation({ 2000, 2000, 2000 });
	u[0]->SetRelativeLocation({ 1,1,1 });
	u[1]->SetRelativeLocation({ 10,10,10 });
	u[4]->SetRelativeLocation({ 1000,1000,1000 });
	u[2]->SetRelativeLocation({ 100,100,100 });
	u[3]->SetRelativeLocation({ 200,200,200 });

	//u[1]->SetRelativeScale3D({ 2,2,2 });

	u[1]->SetRelativeScale3D({ 2,2,2 });

	for(int i=0;i<6;i++)
	{
		u[i]->PrintLoc(std::wstring(L"u[") + std::to_wstring(i) + std::wstring(L"]"));
		//comp->Update();
	}


	//u[0]->PrintLoc(std::wstring(L"u[0]"));
	//u[1]->PrintLoc(std::wstring(L"u[1]"));

	return 0;







	CRenderer::Instance()->Init(hWnd);
	ID3D11Device* device = CRenderer::Instance()->GetGraphics()->GetDevice();
	ID3D11DeviceContext* deviceContext = CRenderer::Instance()->GetGraphics()->GetDeviceContext();

	UCubeComp* cube = new UCubeComp();
	CVertexShader* vertex = new CVertexShader(device);
	CPixelShader* pixel = new CPixelShader(device);
	vertex->Create(L"Shader.hlsl", "VS", "vs_5_0");
	pixel->Create(L"Shader.hlsl", "PS", "ps_5_0");
	cube->Init(vertex, pixel);

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		CRenderer::Instance()->GetGraphics()->RenderBegin();


		//cube->Render();
		CRenderer::Instance()->GetGraphics()->RenderEnd();
	}
	return 0;
}