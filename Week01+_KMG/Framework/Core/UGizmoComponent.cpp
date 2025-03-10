#include "stdafx.h"
#include "UGizmoComponent.h"
#include "UArrowComponent.h"
#include "UDiscHollowComponent.h"

#define GIZMO_SELECT_MOUSE_SPEED_TRANSLATION 10.0f;
#define GIZMO_SELECT_MOUSE_SPEED_ROTATION 30.0f;

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

	DiscX = new UDiscHollowComponent(EPrimitiveColor::RED_X, 0.95);
	DiscY = new UDiscHollowComponent(EPrimitiveColor::GREEN_Y, 0.95);
	DiscZ = new UDiscHollowComponent(EPrimitiveColor::BLUE_Z, 0.95);

	DiscX->AttachToComponent(this);
	DiscY->AttachToComponent(this);
	DiscZ->AttachToComponent(this);

	DiscX->SetRelativeRotation({ 0, 0 , - M_PI/2 + 0.00001});
	DiscY->SetRelativeRotation({ 0,0,0 });
	DiscZ->SetRelativeRotation({ M_PI / 2 ,0,0 });

	DiscX->SetRelativeScale3D({ 2.5, 2.5, 2.5 });
	DiscY->SetRelativeScale3D({ 2.5, 2.5, 2.5 });
	DiscZ->SetRelativeScale3D({ 2.5, 2.5, 2.5 });
}

UGizmoComponent::~UGizmoComponent()
{
	ArrowX->AttachToComponent(nullptr);
	ArrowY->AttachToComponent(nullptr);
	ArrowZ->AttachToComponent(nullptr);
	DiscX->AttachToComponent(nullptr);
	DiscY->AttachToComponent(nullptr);
	DiscZ->AttachToComponent(nullptr);
	ArrowX = ArrowY = ArrowZ = nullptr;
	DiscX = DiscY = DiscZ = nullptr;
}

void UGizmoComponent::Update()
{
 	if (AttachedParent == nullptr)
		return;

	// gizmo의 방향과 크기만 따라감
	this->SetRelativeLocation(AttachedParent->GetRelativeLocation());
	float scaleMax = 1.f;
	scaleMax = max(scaleMax, abs(AttachedParent->GetRelativeScale3D().x)/2);
	scaleMax = max(scaleMax, abs(AttachedParent->GetRelativeScale3D().y)/2);
	scaleMax = max(scaleMax, abs(AttachedParent->GetRelativeScale3D().z)/2);
	this->SetRelativeScale3D({ scaleMax ,scaleMax ,scaleMax });


	UArrowComponent* selectedArrow = nullptr;
	UDiscHollowComponent* selectedDisc = nullptr;
	if (selectedAxis == EPrimitiveColor::RED_X) selectedArrow = ArrowX;
	else if (selectedAxis == EPrimitiveColor::GREEN_Y) selectedArrow = ArrowY;
	else if (selectedAxis == EPrimitiveColor::BLUE_Z) selectedArrow = ArrowZ;
	else if (selectedAxis == EPrimitiveColor::RED_X_ROT) 
		selectedDisc = DiscX;
	else if (selectedAxis == EPrimitiveColor::GREEN_Y_ROT) 
		selectedDisc = DiscY;
	else if (selectedAxis == EPrimitiveColor::BLUE_Z_ROT) selectedDisc = DiscZ;
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


	if (selectedArrow)
	{
		auto cam = CRenderer::Instance()->GetMainCamera();
		FVector arrowDirOnScreen = (FVector4(selectedArrow->Front(), 0) * cam->View() * cam->PerspectiveProjection()).xyz();
		// normalize?

		float effectiveMovement = mouseDirOnScreen.Dot(arrowDirOnScreen);
		effectiveMovement *= GIZMO_SELECT_MOUSE_SPEED_TRANSLATION;

 		auto newPos = selectedArrow->Front() * effectiveMovement + AttachedParent->GetRelativeLocation();
		AttachedParent->SetRelativeLocation(newPos);

		return;
	}
	else if (selectedDisc)
	{
		int xInt, yInt;
		Input::Instance()->GetMouseLocation(xInt, yInt);
		float x = xInt / (float)SCR_WIDTH;
		float y = -yInt / (float)SCR_HEIGHT;

		FVector cursorPosOnScreen = { x,y,0 };

		int dxInt, dyInt;
		Input::Instance()->GetMouseDelta(dxInt, dyInt);

		float dx = dxInt / (float)SCR_WIDTH;
		float dy = -dyInt / (float)SCR_HEIGHT;

		FVector cursorDeltaOnScreen = { dx,dy,0 };

		auto cam = CRenderer::Instance()->GetMainCamera();
		FVector gizmoCenterOnScreen = (FVector4(GetComponentLocation(), 1.f) * cam->View() * cam->PerspectiveProjection()).GetCoord();
		gizmoCenterOnScreen = FVector(gizmoCenterOnScreen.x, gizmoCenterOnScreen.y, 0);
		FVector cursorToGizmo = gizmoCenterOnScreen - cursorPosOnScreen;

		FVector effectiveMovementVector = cursorToGizmo.Cross(cursorDeltaOnScreen);
		float effectiveMovementClockwise = effectiveMovementVector.z;

		//FVector discClockWiseOnScreen = (FVector4(selectedDisc->Right() * -1, 0) * cam->View() * cam->PerspectiveProjection()).xyz();
		// normalize?

		//float effectiveMovement = mouseDirOnScreen.Dot(discClockWiseOnScreen);
		effectiveMovementClockwise *= -GIZMO_SELECT_MOUSE_SPEED_ROTATION;
		FVector rotDirection = { 0,0,0 };
		if (selectedAxis == EPrimitiveColor::RED_X_ROT)
		{
			rotDirection = FVector(1, 0, 0);
		}
		else if (selectedAxis == EPrimitiveColor::GREEN_Y_ROT)
		{
			rotDirection = FVector(0, 1, 0);
		}
		else if (selectedAxis == EPrimitiveColor::BLUE_Z_ROT)
		{
			rotDirection = FVector(0, 0, -1);
		}
		//FVector rotationDirection = { selectedDisc->GetRelativeRotation().x , selectedDisc->GetRelativeRotation().y, selectedDisc->GetRelativeRotation().z };
		auto newRot = rotDirection * effectiveMovementClockwise + AttachedParent->GetRelativeRotation();
		AttachedParent->SetRelativeRotation(newRot);

		return;
	}
}

void UGizmoComponent::Render()
{
	if (isGizmoActivated) {
		{
			ArrowX->Render();
			ArrowY->Render();
			ArrowZ->Render();
			DiscX->Render();
			DiscY->Render();
			DiscZ->Render();
		}
	}
}

//FMatrix UGizmoComponent::GetComponentTransform() const
//{
//	FVector scale3D = AttachedParent->GetComponentScale();
//	return FMatrix::Scale(scale3D)*FMatrix::Translate(AttachedParent->GetComponentLocation());
//}

void UGizmoComponent::AttachTo(UPrimitiveComponent* Parent)
{
	isGizmoActivated = true;
	AttachedParent = Parent;

	//DiscX->AttachToComponent(Parent);
	//DiscY->AttachToComponent(Parent);
	//DiscZ->AttachToComponent(Parent);

	//this->AttachToComponent(Parent);
}

void UGizmoComponent::Detach()
{
	isGizmoActivated = false;
	selectedAxis = EPrimitiveColor::NONE;
	AttachedParent = nullptr;
	//UE_LOG(L"Detach!!!!!!!\n");

	//DiscX->AttachToComponent(nullptr);
	//DiscY->AttachToComponent(nullptr);
	//DiscZ->AttachToComponent(nullptr);


	//this->AttachToComponent(nullptr);
}
