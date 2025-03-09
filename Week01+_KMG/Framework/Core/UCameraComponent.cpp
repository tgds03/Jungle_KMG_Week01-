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
		RelativeLocation += Front() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_S) ) {
		//RelativeLocation.z += 1.0f * Time::GetDeltaTime();
		RelativeLocation -= Front() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_SPACE) ) {
		//RelativeLocation.y += 1.0f * Time::GetDeltaTime();
		RelativeLocation += Up() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_LSHIFT) ) {
		//RelativeLocation.y -= 1.0f * Time::GetDeltaTime();
		RelativeLocation -= Up() * Time::GetDeltaTime();
	}
	if ( Input::Instance()->IsKeyDown(DIK_Q) ) {
		UE_LOG(FMatrix::MakeFromZ(Front()).to_wstring().c_str());
	}
	if ( Input::Instance()->IsMouseButtonDown(1) ) {
		int dx, dy;
		Input::Instance()->GetMouseDelta(dx, dy);
		RelativeRotation.y -= degToRad(dx) * mouseSensitive;
		RelativeRotation.x -= degToRad(dy) * mouseSensitive;
		
	}
	//OutputDebugString((std::to_wstring(dx) + L"\n").c_str());
}

void UCameraComponent::Render() {
	ImGui::Begin("Camera");
	//ImGui::Text(("position: " + static_cast<std::string>(RelativeLocation)).c_str());
	//ImGui::Text(("rotation: " + static_cast<std::string>(RelativeRotation)).c_str());
	ImGui::Checkbox("Orthogonal", &orthogonal);
	ImGui::SliderFloat("FOV", &fieldOfView, 10.f, 90.f);
	ImGui::SliderFloat3("position", &RelativeLocation.x, -50.f, 50.f);
	ImGui::SliderFloat3("rotation", &RelativeRotation.x, -M_PI, M_PI);

	ImGui::End();
}

FMatrix UCameraComponent::View()
{
	return GetRelativeTransform().Inverse();





	//FVector eye = GetRelativeLocation();
	//FVector at = GetRelativeLocation() + FVector(0, 0, 1);
	//FVector up = FVector(0, 1, 0);

	////eye = FVector(eye.x, eye.y, -eye.z);
	////at = FVector(at.x, at.y, -at.z);
	////up = FVector(up.x, up.y, -up.z);
	//FVector n = (eye - at) / (eye - at).Magnitude();
	//FVector u = up.Cross(n) / up.Cross(n).Magnitude();
	//FVector v = n.Cross(u);

	//FMatrix view = {
	//	u.x, v.x, n.x, 0,
	//	u.y, v.y, n.y, 0,
	//	u.z, v.z, n.z, 0,
	//	-eye.x, -eye.y, -eye.z, 1
	//};


	////view = view.Transpose();

	//return view;



	//FMatrix Trnasform = GetComponentTransform();
	//FVector4 u = FVector4((FVector4(1, 0, 0, 0) * Trnasform).xyz(), 1.f);
	//FVector4 v = FVector4((FVector4(0, 1, 0, 0) * Trnasform).xyz(), 1.f);
	//FVector4 n = FVector4((FVector4(0, 0, 1, 0) * Trnasform).xyz(), 1.f);

	//FMatrix Rotation = { u,v,n,FVector4(0,0,0,1) };

	FVector T = GetComponentLocation();
	FMatrix mat =
	{
		Right().x, Up().x, Front().x, 0,
		Right().y, Up().y, Front().y, 0,
		Right().z, Up().z, Front().z, 0,
		-T.Dot(Right()), -T.Dot(Up()), -T.Dot(Front()), 1
	};
	mat = mat.Transpose();
	
	//mat = this->GetComponentTransform().Transpose();


	//return FMatrix::Identity;
	return mat;
}

FMatrix UCameraComponent::Projection() {
	if ( orthogonal )
		return OrthgonalProjection();
	else
		return PerspectiveProjection();
}

FMatrix UCameraComponent::OrthgonalProjection() {
	float zRange = farDistance - nearDistance;
	return FMatrix({ 
		2.f / aspectRatio, 0.f, 0.f, 0.f, 
		0.f, 2.f, 0.f, 0.f,
		0.f, 0.f, 1.f / zRange, - nearDistance / zRange,
		0.f, 0.f, 0.f, 1.f
	});
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
	float yScale = 1.0f / tanf(degToRad(fieldOfView * 0.5f)); // cot(FOV/2)
	float xScale = yScale / aspectRatio;
	float zRange = farDistance - nearDistance;

	return FMatrix({
		 xScale,  0.0f,   0.0f,                         0.0f ,
		 0.0f,    yScale, 0.0f,                         0.0f,
		 0.0f,    0.0f,   farDistance / zRange,                1.0f ,
		 0.0f,    0.0f,  -nearDistance * farDistance / zRange,        0.0f 
		});
	//return FMatrix({
	//	1 / (t * aspectRatio), 0, 0, 0,
	//	0, 1 / t, 0, 0,
	//	0, 0, (farDistance + nearDistance) / (farDistance - nearDistance), -farDistance * nearDistance / (farDistance - nearDistance),
	//	0, 0, 1, 0
	//	});
}
