#include "stdafx.h"
#include "UWorld.h"
#include "Framework/Core/UGizmoComponent.h"

extern UGizmoComponent* gGizmo;

UWorld::UWorld()
{
    UCameraComponent* camera = SpawnCamera();
    CRenderer::Instance()->SetCamera(camera);
    AddActor(camera);
    SpawnCoordArrowActor();
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
    UCameraComponent* cam = nullptr;
    while (!actorList.empty()) // ����Ʈ�� �� ������ �ݺ�
    {
        UActorComponent* actor = actorList.front();
        UCameraComponent* downcast = dynamic_cast<UCameraComponent*>(actor);
        actorList.pop_front();
        if ( downcast ) {
            cam = downcast;
            continue;
        }
        
        delete actor;
    }
    if (cam)
        AddActor(cam);
}

UActorComponent* UWorld::PickingByRay(int mouse_X, int mouse_Y, UArrowComponent* AxisXComp, UArrowComponent* AxisYComp, UArrowComponent* AxisZComp)
{
    UCameraComponent* mainCamera = CRenderer::Instance()->GetMainCamera();
    if (!mainCamera) return nullptr;
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
    EAxisColor pickedAxis = EAxisColor::NONE; 

    if (AxisXComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitAxisXDistance)) {
        if (hitAxisXDistance < minDistance) {
            minDistance = hitAxisXDistance;
            pickedAxis = EAxisColor::RED_X;
        }
    }
    if (AxisYComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitAxisYDistance)) {
        if (hitAxisYDistance < minDistance) {
            minDistance = hitAxisYDistance;
            pickedAxis = EAxisColor::GREEN_Y;
        }
    }
    if (AxisZComp->PickObjectByRayIntersection(pickPosition, viewMatrix, &hitAxisZDistance)) {
        if (hitAxisZDistance < minDistance) {
            minDistance = hitAxisZDistance;
            pickedAxis = EAxisColor::BLUE_Z;
        }
    }
    if (pickedAxis != EAxisColor::NONE) {
        SetAxisPicked(AxisXComp, AxisYComp, AxisZComp, pickedAxis);
        return nullptr;
    }

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
    return nearestActorComp;
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
    return SpawnActor<UCoordArrowComponent>(false);
}

void UWorld::SaveWorld(const FString& fileName)
{
    auto actorListCopy = actorList;  // ���纻 ����
    DataManager::Instance()->SaveWorldToJson(this, fileName);
    //DataManager::Instance()->SaveWorldToJson(this, fileName);
}

void UWorld::LoadWorld(const FString& fileName)
{
    ClearWorld();

    TArray<PrimitiveData> primitives = DataManager::Instance()->LoadWorldFromJson(fileName);

    for (const auto& primitive : primitives)
    {
        if (primitive.Type == "Cube") 
        {
            UCubeComponent* cube = SpawnCubeActor();
            cube->SetRelativeLocation(primitive.Location);
            cube->SetRelativeRotation(primitive.Rotation);
            cube->SetRelativeScale3D(primitive.Scale);
        }
        else if (primitive.Type == "Sphere")
        {
            USphereComponent* sphere = SpawnSphereActor();
            sphere->SetRelativeLocation(primitive.Location);
            sphere->SetRelativeRotation(primitive.Rotation);
            sphere->SetRelativeScale3D(primitive.Scale);
        }
        else if (primitive.Type == "Plane") 
        {
            UPlaneComponent* plane = SpawnPlaneActor();
            plane->SetRelativeLocation(primitive.Location);
            plane->SetRelativeRotation(primitive.Rotation);
            plane->SetRelativeScale3D(primitive.Scale);
        }
    }
}

UDiscComponent* UWorld::SpawnDiscActor()
{
    return SpawnActor<UDiscComponent>();
}

UDiscHollowComponent* UWorld::SpawnDiscHollowActor()
{
    return SpawnActor<UDiscHollowComponent>();
}
