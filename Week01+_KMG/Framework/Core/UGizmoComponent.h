#pragma once
#include "USceneComponent.h"

class UPrimitiveComponent;
class UArrowComponent;

class UGizmoComponent :
    public USceneComponent
{
public:
    UGizmoComponent();
    //UGizmoComponent();
    ~UGizmoComponent();
    virtual void Update();
    virtual void Render() override;
    //virtual FMatrix GetComponentTransform() const override;
    void AttachTo(UPrimitiveComponent* Parent);
    void Detach();

    EPrimitiveColor selectedAxis = EPrimitiveColor::NONE;
    bool isGizmoActivated = false;
    
    // world좌표계 기준으로 할 경우에는 실제 scenecomponent의 parent는 nullptr로함
    UPrimitiveComponent* AttachedComponent;

    UArrowComponent* ArrowX;
    UArrowComponent* ArrowY;
    UArrowComponent* ArrowZ;
};

