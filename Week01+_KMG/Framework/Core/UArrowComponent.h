#pragma once
#include "Framework/Core/UPrimitiveComponent.h"
enum EAxisColor
{
	RED_X,
	GREEN_Y,
	BLUE_Z
};
static const FVector AxisColors[] = {
	FVector(1.0f, 0.0f, 0.0f),  // X��: ����
	FVector(0.0f, 1.0f, 0.0f),  // Y��: �ʷ�
	FVector(0.0f, 0.0f, 1.0f)   // Z��: �Ķ�
};

class UArrowComponent:public UPrimitiveComponent
{
public:
	UArrowComponent(EAxisColor axis);
	~UArrowComponent();
	void LoadObjAndComputeBoundingBox();
	bool IsPicked() { return picked; }
	void SetPicked(bool pik) { picked = pik; }
	virtual bool IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist);
private:
	//for boundBox
	FVector minPos;
	FVector maxPos;
	// picking
	bool picked = false;
};

