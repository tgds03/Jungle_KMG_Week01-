#pragma once
#include "./Framework/Core/USceneComponent.h"
class UCameraComponent :public USceneComponent {
public:
	virtual void Update();
	FMatrix InverseTransformation();
	FMatrix PerspectiveProjection();
	float fieldOfView = 60.f;
	float aspectRatio = 800.f / 600.f;
	float nearDistance = 1.01f, farDistance = 100.f;
};

