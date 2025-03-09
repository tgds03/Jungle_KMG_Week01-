#include "stdafx.h"
#include "UWorld.h"

UWorld::UWorld()
{
    CRenderer::Instance()->SetCamera(SpawnCamera());
}

UWorld::~UWorld()
{
    for (auto* comp : actorList)
    {
        delete comp;
    }
    actorList.clear();
}

void UWorld::Update()
{
    for (auto* comp : actorList)
    {
        auto current = comp;
        if (current) comp->Update();
    }
}

void UWorld::Render()
{
    for (auto* comp : actorList)
    {
        auto current = comp;
        if (current) comp->Render();
    }
}

void UWorld::AddActor(UActorComponent* comp)
{
    actorList.push_back(comp);
}

void UWorld::RemoveActor(UActorComponent* comp)
{
    actorList.remove(comp);
}

void UWorld::PickingByRay(LPARAM lParam)
{
	UCameraComponent* mainCamera = CRenderer::Instance()->GetMainCamera();
	
	FMatrix viewMatrix = mainCamera->GetComponentTransform().Inverse();
	FMatrix projectionMatrix = mainCamera->PerspectiveProjection();
	D3D11_VIEWPORT viewport = CRenderer::Instance()->GetGraphics()->GetViewport();

	float size_x = LOWORD(lParam);
	float size_y = HIWORD(lParam);

	FVector ndcPosition;
	ndcPosition.x = (2.0f * size_x / viewport.Width) - 1.0f;
	ndcPosition.y = 1.0f - (2.0f * size_y / viewport.Height); // DX11은 Y축 반전 없음
	ndcPosition.z = 1.0f; // Near Plane


	FVector nearPoint = FVector(ndcPosition.x, ndcPosition.y, 0.0f); // Near Plane
	FVector farPoint = FVector(ndcPosition.x, ndcPosition.y, 1.0f);  // Far Plane


	FMatrix invProjMatrix = projectionMatrix.Inverse();
	FVector nearPointView = invProjMatrix.TransformCoord(FVector4(nearPoint, 1.0f));
	FVector farPointView = invProjMatrix.TransformCoord(FVector4(farPoint, 1.0f));



	FMatrix invViewMatrix = viewMatrix.Inverse();
	FVector nearPointWorld = invViewMatrix.TransformCoord(FVector4(nearPointView, 1.0f));
	FVector farPointWorld = invViewMatrix.TransformCoord(FVector4(farPointView, 1.0f));


	FVector rayOrigin = nearPointWorld; //
	FVector rayDirection = (farPointWorld - nearPointWorld).Normalized(); // Ray 방향

	// 디버깅 출력
	OutputDebugString((L"Ray Origin (World): x=" + std::to_wstring(rayOrigin.x) +
		L", y=" + std::to_wstring(rayOrigin.y) +
		L", z=" + std::to_wstring(rayOrigin.z) + L"\n").c_str());

	OutputDebugString((L"Ray Direction (World): x=" + std::to_wstring(rayDirection.x) +
		L", y=" + std::to_wstring(rayDirection.y) +
		L", z=" + std::to_wstring(rayDirection.z) + L"\n").c_str());

	for (const auto& actorComp : actorList) {
		actorComp->GenerateRayForPicking(rayOrigin, rayDirection, viewMatrix);
	}
}


UCameraComponent* UWorld::SpawnCamera()
{
    UCameraComponent* newCamera = SpawnActor<UCameraComponent>();
    newCamera->SetRelativeLocation({ 0, 0, -5.0f });
    return newCamera;
}

UCubeComponent* UWorld::SpawnCubeActor()
{
    return SpawnActor<UCubeComponent>();
}

USphereComponent* UWorld::SpawnSphereACtor()
{
    return SpawnActor<USphereComponent>();
}

UPlaneComponent* UWorld::SpawnPlaneActor()
{
    return SpawnActor<UPlaneComponent>();
}

UCoordArrowComponent* UWorld::SpawnCoordArrowActor()
{
    return SpawnActor<UCoordArrowComponent>();
}
