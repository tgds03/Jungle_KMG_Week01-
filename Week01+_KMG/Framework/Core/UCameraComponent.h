#pragma once
#include "./Framework/Core/USceneComponent.h"
class UCameraComponent :public USceneComponent {
public:
	virtual void Update();
	virtual void Render();
	FMatrix View();
	FMatrix PerspectiveProjection();
	float fieldOfView = 60.f;
	float aspectRatio = SCR_WIDTH / (float)SCR_HEIGHT;
	float nearDistance = 1.01f, farDistance = 100.f;
	float mouseSensitive = 0.5f;

private:
	//FMatrix CalculateLookAtLHS(FVector front, FVector up, FVector pos);
};

