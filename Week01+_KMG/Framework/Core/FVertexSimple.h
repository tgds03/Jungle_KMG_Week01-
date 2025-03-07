#pragma once
#include "stdafx.h"

struct FVertexSimple
{
	float x, y, z;	 // Position
	float r, g, b, a; // Color
	static TArray<D3D11_INPUT_ELEMENT_DESC> descs;
};