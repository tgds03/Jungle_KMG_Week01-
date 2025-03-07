#include "stdafx.h"
#include "USceneComponent.h"

FMatrix USceneComponent::Transformation() {
	FMatrix transformation = FMatrix::Scale(RelativeScale3D.x, RelativeScale3D.y, RelativeScale3D.z);
	transformation = transformation * FMatrix::RotateX(RelativeRotation.x);
	transformation = transformation * FMatrix::RotateY(RelativeRotation.y);
	transformation = transformation * FMatrix::RotateZ(RelativeRotation.z);
	transformation = transformation * FMatrix::Translate(RelativeLocation.x, RelativeLocation.y, RelativeLocation.z);
	return transformation;
}
