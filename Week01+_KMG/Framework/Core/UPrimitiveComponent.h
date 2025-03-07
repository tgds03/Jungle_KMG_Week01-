#pragma once
#include "USceneComponent.h"

class UPrimitiveComponent :
    public USceneComponent
{
private:
    bool bVisible = true;
     
public:
    void setVisible(const bool bValue);
};

