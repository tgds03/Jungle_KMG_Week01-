#pragma once
#include "UObject.h"
class UActorComponent :public UObject {

public:
	UActorComponent() {};

	virtual void Update() {};
	virtual void Render() {};
};

