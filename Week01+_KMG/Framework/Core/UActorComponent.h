#pragma once
#include "Framework/Core/UObject.h"
class UActorComponent :public UObject {

public:
	UActorComponent() {};

	virtual void Update();
	//virtual void Render();
};

