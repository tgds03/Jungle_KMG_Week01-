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

void UWorld::PickingByRay()
{
	UCameraComponent* mainCamera = CRenderer::Instance()->GetMainCamera();
	
	FMatrix viewMatrix = mainCamera->GetComponentTransform().Inverse();
	FMatrix projectionMatrix = mainCamera->PerspectiveProjection();
	D3D11_VIEWPORT viewport = CRenderer::Instance()->GetGraphics()->GetViewport();

	int mouse_X;
	int mouse_Y;
	Input::Instance()->GetMouseLocation(mouse_X, mouse_Y);

	FVector pickPosition;
    pickPosition.x = ((2.0f * mouse_X / viewport.Width) - 1.0f) / projectionMatrix[0][0];
    pickPosition.y = - ((2.0f * mouse_Y / viewport.Height)- 1.f) / projectionMatrix[1][1];
    pickPosition.z = 1.0f; // Near Plane
    float hitDistance = FLT_MAX;
    float nearestDistance = FLT_MAX;
   
	for (const auto& actorComp : actorList) {
		actorComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitDistance);
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
