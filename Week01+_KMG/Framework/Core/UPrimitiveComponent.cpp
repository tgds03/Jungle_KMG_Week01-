#include "stdafx.h"
#include "UPrimitiveComponent.h"

void UPrimitiveComponent::Update()
{
}

void UPrimitiveComponent::Render()
{
	if (bVisible)
	{
		Render();
	}
}

void UPrimitiveComponent::setVisible(const bool bValue)
{
	bVisible = bValue;
}
