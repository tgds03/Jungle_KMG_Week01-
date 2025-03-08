#include "stdafx.h"
#include "UCameraComponent.h"

void UCameraComponent::Update() {
	if ( Input::Instance()->IsKeyDown(DIK_A) ) {
		RelativeLocation.x -= 1.0f * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_D) ) {
		RelativeLocation.x += 1.0f * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_W) ) {
		RelativeLocation.z += 1.0f * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_S) ) {
		RelativeLocation.z -= 1.0f * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_SPACE) ) {
		RelativeLocation.y += 1.0f * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_LSHIFT) ) {
		RelativeLocation.y -= 1.0f * Time::GetDeltaTime();
	}
	OutputDebugString((std::to_wstring(RelativeLocation.y) + L"\n").c_str());
}

FMatrix UCameraComponent::InverseTransformation() {
	FMatrix m = FMatrix::Translate(-RelativeLocation.x, -RelativeLocation.y, -RelativeLocation.z);
	m = m * FMatrix::RotateZ(-RelativeRotation.z);
	m = m * FMatrix::RotateY(-RelativeRotation.y);
	m = m * FMatrix::RotateX(-RelativeRotation.x);
	m = m * FMatrix::Scale(1 / RelativeScale3D.x, 1 / RelativeScale3D.y, 1 / RelativeScale3D.z);
	return m;
}
