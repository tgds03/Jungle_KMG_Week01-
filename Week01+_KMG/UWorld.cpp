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

void UWorld::PickingByRay(int mouse_X, int mouse_Y, UArrowComponent* AxisXComp, UArrowComponent* AxisYComp, UArrowComponent* AxisZComp)
{
    UCameraComponent* mainCamera = CRenderer::Instance()->GetMainCamera();

    FMatrix viewMatrix = mainCamera->GetComponentTransform().Inverse();
    FMatrix projectionMatrix = mainCamera->PerspectiveProjection();
    D3D11_VIEWPORT viewport = CRenderer::Instance()->GetGraphics()->GetViewport();

    //Input::Instance()->GetMouseLocation(mouse_X, mouse_Y);

    FVector pickPosition;
    pickPosition.x = ((2.0f * mouse_X / viewport.Width) - 1) / projectionMatrix[0][0];
    pickPosition.y = -((2.0f * mouse_Y / viewport.Height) - 1) / projectionMatrix[1][1];
    pickPosition.z = 1.0f; // Near Plane
    float hitDistance = FLT_MAX;
    float nearestDistance = FLT_MAX;
    UActorComponent* nearestActorComp = nullptr;

    if (AxisXComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitDistance)) {

        UE_LOG(L"X__AXIS \n");
        SetAxisPicked(AxisXComp, AxisYComp, AxisZComp, EPrimitiveColor::RED_X);
        return;
    }
    if (AxisYComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitDistance)) {
        UE_LOG(L"Y__AXIS \n");
        SetAxisPicked(AxisXComp, AxisYComp, AxisZComp, EPrimitiveColor::GREEN_Y);
        return;
    }
    if (AxisZComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitDistance)) {
        UE_LOG(L"Z__AXIS \n");
        SetAxisPicked(AxisXComp, AxisYComp, AxisZComp, EPrimitiveColor::BLUE_Z);
        return;
    }
    SetAxisPicked(AxisXComp, AxisYComp, AxisZComp, static_cast<EPrimitiveColor>(-1));
    AxisXComp->SetPicked(false);
    AxisYComp->SetPicked(false);
    AxisZComp->SetPicked(false);
	for (const auto& actorComp : actorList) {
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



UCameraComponent* UWorld::SpawnCamera()
{
    UCameraComponent* newCamera = SpawnActor<UCameraComponent>();
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

UDiscComponent* UWorld::SpawnDiscActor()
{
    return SpawnActor<UDiscComponent>();
}

UDiscHollowComponent* UWorld::SpawnDiscHollowActor()
{
    return SpawnActor<UDiscHollowComponent>();
}
