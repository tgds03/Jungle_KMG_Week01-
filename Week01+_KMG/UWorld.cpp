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
