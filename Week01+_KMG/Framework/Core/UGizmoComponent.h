#pragma once
#include "USceneComponent.h"
#include "UDiscHollowHalfComponent.h"

class UPrimitiveComponent;
class UArrowComponent;
class UDiscHollowComponent;

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
    bool isTranslationAbolute = true;
    //int Mode = 0; // 0 for translation, 1 for rotation, 2 for scaling
    
    // world좌표계 기준으로 할 경우에는 실제 scenecomponent의 parent는 nullptr로함
    UPrimitiveComponent* AttachedParent;

    UArrowComponent* ArrowX;
    UArrowComponent* ArrowY;
    UArrowComponent* ArrowZ;
    UArrowComponent* temp;

    UDiscHollowComponent* DiscX;
    UDiscHollowComponent* DiscY;
    UDiscHollowComponent* DiscZ;
    UDiscHollowComponent* temp1;
};

