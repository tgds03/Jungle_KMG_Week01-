#include "stdafx.h"
#include "UWorld.h"
#include "Framework/Core/UGizmoComponent.h"

extern UGizmoComponent* gGizmo;

UWorld::UWorld()
{
    CRenderer::Instance()->SetCamera(SpawnCamera());
}

UWorld::~UWorld()
{
    ClearWorld();
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
    delete comp;
}

void UWorld::ClearWorld()
{
    gGizmo->Detach();
    while (!actorList.empty()) // 리스트가 빌 때까지 반복
    {
        delete actorList.front();
        actorList.pop_front();
    }
}

void UWorld::PickingByRay(int mouse_X, int mouse_Y, UArrowComponent* AxisXComp, UArrowComponent* AxisYComp, UArrowComponent* AxisZComp)
{
    UCameraComponent* mainCamera = CRenderer::Instance()->GetMainCamera();
    if (!mainCamera) return;
    FMatrix viewMatrix = mainCamera->GetComponentTransform().Inverse();
    FMatrix projectionMatrix = mainCamera->PerspectiveProjection();
    D3D11_VIEWPORT viewport = CRenderer::Instance()->GetGraphics()->GetViewport();

    //Input::Instance()->GetMouseLocation(mouse_X, mouse_Y);

    FVector pickPosition;
    pickPosition.x = ((2.0f * mouse_X / viewport.Width) - 1) / projectionMatrix[0][0];
    pickPosition.y = -((2.0f * mouse_Y / viewport.Height) - 1) / projectionMatrix[1][1];
    pickPosition.z = 1.0f; // Near Plane
    float hitAxisXDistance = FLT_MAX;
    float hitAxisYDistance = FLT_MAX;
    float hitAxisZDistance = FLT_MAX;
    float minDistance = FLT_MAX;
    EPrimitiveColor pickedAxis = EPrimitiveColor::NONE; 

    if (AxisXComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitAxisXDistance)) {
        if (hitAxisXDistance < minDistance) {
            minDistance = hitAxisXDistance;
            pickedAxis = EPrimitiveColor::RED_X;
        }
    }
    if (AxisYComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitAxisYDistance)) {
        if (hitAxisYDistance < minDistance) {
            minDistance = hitAxisYDistance;
            pickedAxis = EPrimitiveColor::GREEN_Y;
        }
    }
    if (AxisZComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitAxisZDistance)) {
        if (hitAxisZDistance < minDistance) {
            minDistance = hitAxisZDistance;
            pickedAxis = EPrimitiveColor::BLUE_Z;
        }
    }
    if (pickedAxis != EPrimitiveColor::NONE) {
        SetAxisPicked(AxisXComp, AxisYComp, AxisZComp, pickedAxis);
        return;
    }

    float hitDistance = FLT_MAX;
    float nearestDistance = FLT_MAX;
    UActorComponent* nearestActorComp = nullptr;

	for (const auto& actorComp : actorList) {
        if (!actorComp) continue;
		bool bRes = actorComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitDistance);
       if (bRes && hitDistance < nearestDistance) {
            nearestActorComp = actorComp;
            nearestDistance = hitDistance;
        }
	}
    if (nearestActorComp) {
        UE_LOG((L"\nfind!__" + std::to_wstring(nearestActorComp->GetUUID()) + L" is neareast!!\n").c_str());
        UE_LOG((L"\nfind!__" + std::to_wstring(nearestActorComp->GetUUID()) + L" is neareast!!\n").c_str());
    }
}

int UWorld::GetActorCount() const
{
    return actorList.size();
}

const TLinkedList<UActorComponent*>& UWorld::GetActors() const
{
    return actorList;
}


UCameraComponent* UWorld::SpawnCamera()
{
    UCameraComponent* newCamera = SpawnActor<UCameraComponent>(false);
    newCamera->SetRelativeLocation({ 0, 0, -5.0f });
    return newCamera;
}

void UWorld::SetAxisPicked(UArrowComponent* axisX, UArrowComponent* axisY, UArrowComponent* axisZ, EPrimitiveColor pickedAxis)
{
    axisX->SetPicked(pickedAxis == EPrimitiveColor::RED_X);
    axisY->SetPicked(pickedAxis == EPrimitiveColor::GREEN_Y);
    axisZ->SetPicked(pickedAxis == EPrimitiveColor::BLUE_Z);
}

UCubeComponent* UWorld::SpawnCubeActor()
{
    return SpawnActor<UCubeComponent>();
}

USphereComponent* UWorld::SpawnSphereActor()
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

UDiscComponent* UWorld::SpawnDiscActor()
{
    return SpawnActor<UDiscComponent>();
}

UDiscHollowComponent* UWorld::SpawnDiscHollowActor()
{
    return SpawnActor<UDiscHollowComponent>();
}
