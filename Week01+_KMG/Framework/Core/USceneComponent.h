#pragma once
#include "Framework/Core/UActorComponent.h"
class USceneComponent :public UActorComponent {
public:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D = FVector::One;

	FMatrix Transformation();
};

