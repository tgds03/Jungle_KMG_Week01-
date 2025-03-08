#pragma once
#include "UPrimitiveComponent.h"
class UCoordArrowComponent :
    public UPrimitiveComponent
{
public:
    UCoordArrowComponent();
    ~UCoordArrowComponent();
    void Render();
    void Update();
};

