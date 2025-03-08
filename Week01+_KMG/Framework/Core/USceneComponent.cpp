#include "stdafx.h"
#include "USceneComponent.h"

FMatrix USceneComponent::Transformation() {
	FMatrix m = FMatrix::Scale(RelativeScale3D.x, RelativeScale3D.y, RelativeScale3D.z);
	m = m * FMatrix::RotateX(RelativeRotation.x);
	m = m * FMatrix::RotateY(RelativeRotation.y);
	m = m * FMatrix::RotateZ(RelativeRotation.z);
	m = m * FMatrix::Translate(RelativeLocation.x, RelativeLocation.y, RelativeLocation.z);
	return m;
}

FVector USceneComponent::Right() {
	FVector4 r = Transformation().r1();
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Up() {
	FVector4 r = Transformation().r2();
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Front() {
	FVector4 r = Transformation().r3();
	return FVector(r.x, r.y, r.z).Normalized();
}
