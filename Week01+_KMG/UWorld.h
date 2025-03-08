#pragma once
#include "Framework/Core/UObject.h"
#include "Framework/Core/UActorComponent.h"
#include "UCubeComponent.h"
#include "USphereComponent.h"

//class UActorComponent;

class UWorld :
    public UObject
{
public:
    UWorld() {}
    ~UWorld();

    void Update();
    void Render();

    void AddActor(UActorComponent* comp);
    void RemoveActor(UActorComponent* comp);

    template <typename T>
    T* SpawnActor(); // RTTI 적용 예정
    template <typename T>
    T* SpawnActor(FVector position, FVector rotation = FVector::Zero, FVector scal = FVector::One);

    UCubeComponent* SpawnCubeActor();
    USphereComponent* SpawnSphereACtor();


private:
    TLinkedList<UActorComponent*> actorList = {};
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

