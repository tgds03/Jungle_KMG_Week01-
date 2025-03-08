#pragma once
#include "Framework/Core/UObject.h"

class UWorld;

class UActorComponent :public UObject {	
public:
	UActorComponent() {}
	virtual ~UActorComponent() {}

	virtual void Update() {};
	virtual void Render() {};

private:
	UWorld* motherScene;
};

