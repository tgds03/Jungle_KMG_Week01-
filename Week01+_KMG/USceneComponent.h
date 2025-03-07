#pragma once
#include "UActorComponent.h"
class USceneComponent :public UActorComponent {
public:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D;

	FMatrix Transformation();
};

