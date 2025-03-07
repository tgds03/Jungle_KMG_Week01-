#pragma once
#include "Framework/Core/UObject.h"

class UActorComponent :public UObject {	
public:
	UActorComponent();
	virtual ~UActorComponent();

	virtual void Update() {};
	virtual void Render() {};

	static void UpdateAll();
	static void RenderAll();
};

