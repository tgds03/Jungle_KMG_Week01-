#include "stdafx.h"
#include "UCameraComponent.h"

void UCameraComponent::Update() {
	if ( !Input::Instance()->IsMouseButtonDown(1) )  {
		if ( Input::Instance()->IsKeyDown(DIK_A) ) {
			RelativeLocation.x -= 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_D) ) {
			RelativeLocation.x += 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_W) ) {
			RelativeLocation.z -= 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_S) ) {
			RelativeLocation.z += 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_SPACE) ) {
			RelativeLocation.y += 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_LSHIFT) ) {
			RelativeLocation.y -= 1.0f * Time::GetDeltaTime();
		}
	} else {
		if ( Input::Instance()->IsKeyDown(DIK_A) ) {
			RelativeRotation.y -= 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_D) ) {
			RelativeRotation.y += 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_W) ) {
			RelativeRotation.x -= 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_S) ) {
			RelativeRotation.x += 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_SPACE) ) {
			RelativeRotation.z += 1.0f * Time::GetDeltaTime();
		}
		if ( Input::Instance()->IsKeyDown(DIK_LSHIFT) ) {
			RelativeRotation.z -= 1.0f * Time::GetDeltaTime();
		}
	}
	//OutputDebugString((std::to_wstring(RelativeLocation.y) + L"\n").c_str());
	//PrintLoc(L"CAMERA");
}

//FMatrix UCameraComponent::InverseTransformation() {
//	FMatrix m = FMatrix::Translate(-RelativeLocation.x, -RelativeLocation.y, -RelativeLocation.z);
//	m = m * FMatrix::RotateZ(-RelativeRotation.z);
//	m = m * FMatrix::RotateY(-RelativeRotation.y);
//	m = m * FMatrix::RotateX(-RelativeRotation.x);
//	//m = m * FMatrix::Scale(1 / RelativeScale3D.x, 1 / RelativeScale3D.y, 1 / RelativeScale3D.z);
//	return m;
//}

FMatrix UCameraComponent::PerspectiveProjection() {
	float t = tan(degToRad(fieldOfView / 2));
	return FMatrix({
			1/(t*aspectRatio), 0, 0, 0,
			0, 1/t, 0, 0,
			0, 0, (farDistance + nearDistance) / (farDistance - nearDistance), - farDistance * nearDistance / (farDistance - nearDistance),
			0, 0, 1, 0
	});
}
