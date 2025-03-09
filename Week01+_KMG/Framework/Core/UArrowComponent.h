#pragma once
#include "./Framework/Core/UPrimitiveComponent.h"
class UArrowComponent :
    public UPrimitiveComponent
{
public:
	UArrowComponent();
	virtual ~UArrowComponent();
	virtual void Update();

	bool isSelected;
};

