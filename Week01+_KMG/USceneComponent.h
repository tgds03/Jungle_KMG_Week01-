#pragma once
#include "UActorComponent.h"
class USceneComponent :public UActorComponent {
public:
	FVector4 RelativeLocation;
	FVector4 RelatvieRotation;
	FVector4 RelativeScale3D;

	FMatrix Transformation();
};

