#pragma once
#include "./Framework/Core/UPrimitiveComponent.h"

class UPlaneComponent :public UPrimitiveComponent {
public:
	UPlaneComponent();
	virtual ~UPlaneComponent();
	bool IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& Distance);
};

