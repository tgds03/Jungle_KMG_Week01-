#include "stdafx.h"
#include "UCameraComponent.h"

void UCameraComponent::Update() {
	if ( Input::Instance()->IsKeyDown(DIK_A) ) {
		//RelativeLocation.x -= 1.0f * Time::GetDeltaTime();
		RelativeLocation -= Right() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_D) ) {
		//RelativeLocation.x += 1.0f * Time::GetDeltaTime();
		RelativeLocation += Right() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_W) ) {
		//RelativeLocation.z -= 1.0f * Time::GetDeltaTime();
		RelativeLocation -= Front() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_S) ) {
		//RelativeLocation.z += 1.0f * Time::GetDeltaTime();
		RelativeLocation += Front() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_SPACE) ) {
		//RelativeLocation.y += 1.0f * Time::GetDeltaTime();
		RelativeLocation += Up() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_LSHIFT) ) {
		//RelativeLocation.y -= 1.0f * Time::GetDeltaTime();
		RelativeLocation -= Up() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsMouseButtonDown(1) ) {
		int dx, dy;
		Input::Instance()->GetMouseDelta(dx, dy);
		RelativeRotation.y += degToRad(dx) * mouseSensitive;
		RelativeRotation.x += degToRad(dy) * mouseSensitive;
		
	}
	//OutputDebugString((std::to_wstring(dx) + L"\n").c_str());
}

void UCameraComponent::Render() {
	ImGui::Begin("Camera");
	ImGui::Text(("position: " + static_cast<std::string>(RelativeLocation)).c_str());
	ImGui::Text(("rotation: " + static_cast<std::string>(RelativeRotation)).c_str());
	ImGui::End();
}

FMatrix UCameraComponent::View()
{
	assert(0);
	return FMatrix::Identity;
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
