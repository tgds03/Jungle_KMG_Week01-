#include "stdafx.h"
#include "UGizmoComponent.h"
#include "UArrowComponent.h"

#define GIZMO_SELECT_MOUSE_SPEED 30.0f;

UGizmoComponent::UGizmoComponent(UArrowComponent* axisX, UArrowComponent* axisY, UArrowComponent* axisZ)
	: ArrowX(axisX), ArrowY(axisY), ArrowZ(axisZ)
{
	ArrowX->AttachToComponent(this);
	ArrowY->AttachToComponent(this);
	ArrowZ->AttachToComponent(this);
	ArrowX->SetRelativeScale3D({ 2,2,2 });
	ArrowY->SetRelativeScale3D({ 2,2,2 });
	ArrowZ->SetRelativeScale3D({ 2,2,2 });
}

void UGizmoComponent::Update()
{
	// 기즈모가 아무것도 안붙어있음
 	if (GetAttachParent() == nullptr)
		return;

	ImGui::Begin("Gizmo");
	ImGui::Text("Gizmo Rel Pos: %f %f %f", RelativeLocation.x, RelativeLocation.y, RelativeLocation.z);
	ImGui::Text("Gizmo Comp Pos: %f %f %f", GetComponentLocation().x, GetComponentLocation().y, GetComponentLocation().z);
	ImGui::Text("Parent Rel Pos: %f %f %f", GetAttachParent()->GetRelativeLocation().x, GetAttachParent()->GetRelativeLocation().y, GetAttachParent()->GetRelativeLocation().z);
	ImGui::Text("Parent Comp Pos: %f %f %f", GetAttachParent()->GetComponentLocation().x, GetAttachParent()->GetComponentLocation().y, GetAttachParent()->GetComponentLocation().z);
	ImGui::End();

	UArrowComponent* selectedArrow = nullptr;
	if (ArrowX->IsPicked()) selectedArrow = ArrowX;
	else if (ArrowY->IsPicked()) selectedArrow = ArrowY;
	else if (ArrowZ->IsPicked()) selectedArrow = ArrowZ;
	else return; 	// 기즈모의 화살표가 선택되지 않음

	UArrowComponent* arrow;
	// 마우스 델타
	int dxInt, dyInt;
	Input::Instance()->GetMouseDelta(dxInt, dyInt);
	float dx = dxInt / (float)SCR_WIDTH;
	float dy = -dyInt / (float)SCR_HEIGHT;
		
 	FVector mouseDirOnScreen = { dx,dy,0 };
	if (abs(dx) < FLT_EPSILON && abs(dy) < FLT_EPSILON) return;
	ImGui::Begin("MouseDelta");
	ImGui::Text("MouseDelta: %f %f", dx, dy);
	ImGui::End();

	auto cam = CRenderer::Instance()->GetMainCamera();
	FVector arrowDirOnScreen = (FVector4(selectedArrow->Front(), 0) * cam->View() * cam->PerspectiveProjection()).xyz();
	// normalize?

	float effectiveMovement = mouseDirOnScreen.Dot(arrowDirOnScreen);
	effectiveMovement *= GIZMO_SELECT_MOUSE_SPEED;

 	auto newPos = selectedArrow->Front() * effectiveMovement + GetAttachParent()->GetRelativeLocation();
	GetAttachParent()->SetRelativeLocation(newPos);
	ImGui::Begin("Gizmo Attached");
	auto l =GetAttachParent()->GetRelativeLocation();
	ImGui::Text("Gizmo Attached Rel Pos: %f %f %f", l.x, l.y, l.z);
	ImGui::End();


}

void UGizmoComponent::AttachTo(UPrimitiveComponent* Parent)
{
	this->AttachToComponent(Parent);
}

void UGizmoComponent::Detach()
{
	this->AttachToComponent(nullptr);
}
