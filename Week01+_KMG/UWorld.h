#pragma once
#include "Framework/Core/UObject.h"
#include "USphereComponent.h"
//#include "Framework/Core/UActorComponent.h"
#include "Framework/Core/UCubeComponent.h"
#include "Framework/Core/UPlaneComponent.h"
#include "Framework/Core/UCoordArrowComponent.h"

class UActorComponent;
class UCubeComponent;
class USphereComponent;
class UPlaneComponent;
class UCoordArrowComponent;

class UWorld :
    public UObject
{
public:
    UWorld() {
        AddActor(CRenderer::Instance()->GetCamera());
    }
    ~UWorld();

    void Update();
    void Render();

    void AddActor(UActorComponent* comp);
    void RemoveActor(UActorComponent* comp);

    UCubeComponent* SpawnCubeActor();
    USphereComponent* SpawnSphereACtor();
    UPlaneComponent* SpawnPlaneActor();
    UCoordArrowComponent* SpawnCoordArrowActor();

private:
    TLinkedList<UActorComponent*> actorList = {};

    template <typename T>
    T* SpawnActor(); // RTTI 적용 후 public으로 변경
    template <typename T>
    T* SpawnActor(FVector position, FVector rotation = FVector::Zero, FVector scal = FVector::One);
};

template<typename T>
inline T* UWorld::SpawnActor()
{
    static_assert(std::is_base_of<UActorComponent, T>::value, "T must be derived from UActorComponent");

    T* newActor = new T();

    if (!newActor)
        return nullptr;

    AddActor(newActor);
    return newActor;
}

template<typename T>
inline T* UWorld::SpawnActor(FVector position, FVector rotation, FVector scal)
{
    static_assert(std::is_base_of<UActorComponent, T>::value, "T must be derived from UActorComponent");

    return nullptr;
}

