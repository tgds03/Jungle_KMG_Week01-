#pragma once
#include "Framework/Core/UActorComponent.h"
class USceneComponent :public UActorComponent {
public:
	FVector RelativeLocation = FVector::Zero;
	FVector RelativeRotation = FVector::Zero;
	FVector RelativeScale3D = FVector::One;

	FMatrix Transformation();

	FVector Right();
	FVector Up();
	FVector Front();
};

