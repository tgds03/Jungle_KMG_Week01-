#pragma once
#include "Framework/Core/UActorComponent.h"

class USceneComponent :public UActorComponent {
public:
	FVector RelativeLocation;
	FVector RelatvieRotation;
	FVector RelativeScale3D;

	FMatrix Transformation();
};

