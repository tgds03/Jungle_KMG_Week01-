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

	ArrowX->SetRelativeRotation({ FLT_EPSILON,-M_PI / 2 + FLT_EPSILON ,FLT_EPSILON });
	ArrowY->SetRelativeRotation({ M_PI / 2 - FLT_EPSILON ,FLT_EPSILON,FLT_EPSILON });
	ArrowZ->SetRelativeRotation({ FLT_EPSILON,FLT_EPSILON,FLT_EPSILON });

	DiscX = new UDiscHollowComponent(EPrimitiveColor::RED_X, 0.95);
	DiscY = new UDiscHollowComponent(EPrimitiveColor::GREEN_Y, 0.95);
	DiscZ = new UDiscHollowComponent(EPrimitiveColor::BLUE_Z, 0.95);

	DiscX->AttachToComponent(this);
	DiscY->AttachToComponent(this);
	DiscZ->AttachToComponent(this);

	DiscX->SetRelativeRotation({ FLT_EPSILON, 0.5 , -M_PI / 2 - FLT_EPSILON });
	DiscY->SetRelativeRotation({ FLT_EPSILON,FLT_EPSILON,FLT_EPSILON });
	DiscZ->SetRelativeRotation({ M_PI / 2 - FLT_EPSILON,FLT_EPSILON,FLT_EPSILON });

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
	float scaleMax = 0.3f;
	scaleMax = max(scaleMax, abs(AttachedParent->GetRelativeScale3D().x)/2);
	scaleMax = max(scaleMax, abs(AttachedParent->GetRelativeScale3D().y)/2);
	scaleMax = max(scaleMax, abs(AttachedParent->GetRelativeScale3D().z)/2);
	scaleMax *= 2.0;
	this->SetRelativeScale3D({ scaleMax ,scaleMax ,scaleMax });

	//isTranslationAbolute = 1;
	if (isTranslationAbolute)
	{
		this->SetRelativeRotation({ 0,0,0 });
		ArrowX->SetRelativeRotation({ FLT_EPSILON,-M_PI / 2 + FLT_EPSILON ,FLT_EPSILON });
		ArrowY->SetRelativeRotation({ M_PI / 2 - FLT_EPSILON ,FLT_EPSILON,FLT_EPSILON });
		ArrowZ->SetRelativeRotation({ FLT_EPSILON,FLT_EPSILON,FLT_EPSILON });
	}
	else
	{
		auto rot = AttachedParent->GetComponentRotation();
		this->SetRelativeRotation(rot);
		//ArrowX->SetRelativeRotation(rot);
		//ArrowY->SetRelativeRotation(rot);
		//ArrowZ->SetRelativeRotation(rot);

		//ArrowX->SetRelativeRotation(rot * -1 + FVector{ FLT_EPSILON, -M_PI / 2 + FLT_EPSILON, FLT_EPSILON });
		//ArrowY->SetRelativeRotation(rot * -1 + FVector{ M_PI / 2 - FLT_EPSILON, FLT_EPSILON, FLT_EPSILON });
		//ArrowZ->SetRelativeRotation(rot * -1 + FVector{ FLT_EPSILON, FLT_EPSILON, FLT_EPSILON });
		
	}
	

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
		if (temp)
		{
			temp->renderFlags &= ~PRIMITIVE_FLAG_SELECTED;
			temp = nullptr;
		}
		if (temp1) {
			temp1->renderFlags &= ~PRIMITIVE_FLAG_SELECTED;
			temp1 = nullptr;
		}
		return; 	// ������� ȭ��ǥ�� ���õ��� ����
	}
	if (selectedArrow)
	{
		temp = selectedArrow;
		temp->renderFlags |= PRIMITIVE_FLAG_SELECTED;
	}
	else if (selectedDisc)
	{
		temp1 = selectedDisc;
		temp1->renderFlags |= PRIMITIVE_FLAG_SELECTED;
	}

	// ���콺 ��Ÿ
	int dxInt, dyInt;
	Input::Instance()->GetMouseDelta(dxInt, dyInt);
	float dx = dxInt / (float)SCR_WIDTH;
	float dy = -dyInt / (float)SCR_HEIGHT;
		
 	FVector mouseDirOnScreen = { dx,dy,0 };
	if (abs(dx) < FLT_EPSILON && abs(dy) < FLT_EPSILON) return;

	if (selectedArrow)
	{
		auto cam = CRenderer::Instance()->GetMainCamera();
		FVector arrowDirOnScreen = (FVector4(selectedArrow->Front(), 0) * cam->View() * cam->PerspectiveProjection()).xyz();
		// normalize?

		float effectiveMovement = mouseDirOnScreen.Dot(arrowDirOnScreen);
		effectiveMovement *= GIZMO_SELECT_MOUSE_SPEED_TRANSLATION;
		effectiveMovement *= scaleMax;

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

void UGizmoComponent::AttachTo(UPrimitiveComponent* Parent)
{
	isGizmoActivated = true;
	AttachedParent = Parent;
}

void UGizmoComponent::Detach()
{
	isGizmoActivated = false;
	selectedAxis = EPrimitiveColor::NONE;
	AttachedParent = nullptr;
}
