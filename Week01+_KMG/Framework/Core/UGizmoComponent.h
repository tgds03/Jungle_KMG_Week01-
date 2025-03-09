#pragma once
#include "USceneComponent.h"

class UPrimitiveComponent;
class UArrowComponent;

class UGizmoComponent :
    public USceneComponent
{
public:
    UGizmoComponent(UArrowComponent* axisX, UArrowComponent* axisY, UArrowComponent* axisZ);
    //UGizmoComponent();
    //~UGizmoComponent();
    virtual void Update();
    void AttachTo(UPrimitiveComponent* Parent);
    void Detach();

private:
    UArrowComponent* ArrowX;
    UArrowComponent* ArrowY;
    UArrowComponent* ArrowZ;
};

