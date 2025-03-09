#pragma once
#include "Framework/Core/UPrimitiveComponent.h"

class USphereComponent :
    public UPrimitiveComponent
{
public:
    USphereComponent();
    virtual ~USphereComponent();
    virtual void Update();
};

