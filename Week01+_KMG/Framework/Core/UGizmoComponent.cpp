#include "stdafx.h"
//#include "UGizmoComponent.h"
//#include "UArrowComponent.h"
//
//#define GIZMO_SELECT_MOUSE_SPEED 1.0f;
//
//UGizmoComponent::UGizmoComponent()
//{
//	ArrowX = new UArrowXComponent;
//	ArrowY = new UArrowYComponent;
//	ArrowZ = new UArrowZComponent;
//}
//
//void UGizmoComponent::Update()
//{
//	// ����� �ƹ��͵� �Ⱥپ�����
//	if (GetAttachParent() == nullptr)
//		return;
//
//	UArrowComponent* selected = nullptr;
//	if (ArrowX->isSelected) selected = ArrowX;
//	else if (ArrowY->isSelected) selected = ArrowY;
//	else if (ArrowZ->isSelected) selected = ArrowZ;
//	else return; 	// ������� ȭ��ǥ�� ���õ��� ����
//
//	UArrowComponent* arrow;
//	// ���콺 ��Ÿ
//	int dxInt, dyInt;
//	Input::Instance()->GetMouseDelta(dxInt, dyInt);
//	float dx = dxInt / (float)SCR_WIDTH;
//	float dy = -dyInt / (float)SCR_HEIGHT;
//		
//	FVector mouseDirOnScreen = { dx,dy,0 };
//
//	auto cam = CRenderer::Instance()->GetMainCamera();
//	FVector arrowDirOnScreen = (FVector4(selected->Front(), 0) * cam->View() * cam->PerspectiveProjection()).xyz();
//	// normalize?
//
//	float effectiveMovement = mouseDirOnScreen.Dot(arrowDirOnScreen);
//	effectiveMovement *= GIZMO_SELECT_MOUSE_SPEED;
//
//	GetAttachParent()->SetRelativeLocation(selected->Front() * effectiveMovement + selected->GetRelativeLocation());
//}
