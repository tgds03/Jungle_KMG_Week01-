#pragma once
#include "./Framework/Core/USceneComponent.h"
class UCameraComponent :public USceneComponent {
public:
	virtual void Update();
	FMatrix InverseTransformation();
};

