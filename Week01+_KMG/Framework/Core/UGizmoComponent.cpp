#include "stdafx.h"
#include "UGizmoComponent.h"
#include "UArrowComponent.h"

#define GIZMO_SELECT_MOUSE_SPEED 10.0f;

UGizmoComponent::UGizmoComponent()
{
	ArrowX = new UArrowComponent(EPrimitiveColor::RED_X);
	ArrowY = new UArrowComponent(EPrimitiveColor::GREEN_Y);
	ArrowZ = new UArrowComponent(EPrimitiveColor::BLUE_Z);

	ArrowX->AttachToComponent(this);
	ArrowY->AttachToComponent(this);
	ArrowZ->AttachToComponent(this);

	ArrowX->SetRelativeRotation({ 0,-M_PI / 2,0 });
	ArrowY->SetRelativeRotation({ M_PI / 2 ,0,0 });
	ArrowZ->SetRelativeRotation({ 0,0,0 });

}

UGizmoComponent::~UGizmoComponent()
{
	ArrowX->AttachToComponent(nullptr);
	ArrowY->AttachToComponent(nullptr);
	ArrowZ->AttachToComponent(nullptr);
	ArrowX = ArrowY = ArrowZ = nullptr;
}

void UGizmoComponent::Update()
{
 	if (AttachedComponent == nullptr)
		return;

	UArrowComponent* selectedArrow = nullptr;
	if (selectedAxis == EPrimitiveColor::RED_X) selectedArrow = ArrowX;
	else if (selectedAxis == EPrimitiveColor::GREEN_Y) selectedArrow = ArrowY;
	else if (selectedAxis == EPrimitiveColor::BLUE_Z) selectedArrow = ArrowZ;
	else {
		return; 	// ������� ȭ��ǥ�� ���õ��� ����
	}

	// ���콺 ��Ÿ
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

 	auto newPos = selectedArrow->Front() * effectiveMovement + AttachedComponent->GetRelativeLocation();
	AttachedComponent->SetRelativeLocation(newPos);

	return;



	//ImGui::Begin("Gizmo Attached");
	//auto l = AttachedComponent->GetRelativeLocation();
	//ImGui::Text("Gizmo Attached Rel Pos: %f %f %f", l.x, l.y, l.z);
	//ImGui::End();

	//USceneComponent* parent = AttachedComponent;
	//FMatrix parentTransform = parent->GetComponentTransform();
	//FMatrix parentTransformInverse = parentTransform.Inverse();
	//FVector parentLocation = parent->GetComponentLocation();
	//FVector parentRotation = parent->GetComponentRotation();
	//FVector parentScale3D = parent->GetComponentScale();

	//FVector worldLocation = (FVector4(parentLocation, 1.f) * parentTransformInverse).GetCoord();
	//FVector worldRotation = (FVector4(parentRotation, 0.f) * parentTransformInverse).xyz();
	//FVector worldScale3D = (FVector4(parentScale3D, 0.f) * parentTransformInverse).xyz();

	//SetRelativeLocation(parentLocation);
	//SetRelativeRotation(parentRotation);
	//SetRelativeScale3D(parentScale3D);

}

void UGizmoComponent::Render()
{
	if (isGizmoActivated) {
		ArrowX->Render();
		ArrowY->Render();
		ArrowZ->Render();
	}
}

//FMatrix UGizmoComponent::GetComponentTransform() const
//{
//	FVector scale3D = AttachedComponent->GetComponentScale();
//	return FMatrix::Scale(scale3D)*FMatrix::Translate(AttachedComponent->GetComponentLocation());
//}

void UGizmoComponent::AttachTo(UPrimitiveComponent* Parent)
{
	isGizmoActivated = true;
	AttachedComponent = Parent;
	this->AttachToComponent(Parent);
}

void UGizmoComponent::Detach()
{
	isGizmoActivated = false;
	selectedAxis = EPrimitiveColor::NONE;
	AttachedComponent = nullptr;
	//UE_LOG(L"Detach!!!!!!!\n");
	this->AttachToComponent(nullptr);
}
