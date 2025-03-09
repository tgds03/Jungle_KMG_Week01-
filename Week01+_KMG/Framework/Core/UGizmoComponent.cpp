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
//	// 기즈모가 아무것도 안붙어있음
//	if (GetAttachParent() == nullptr)
//		return;
//
//	UArrowComponent* selected = nullptr;
//	if (ArrowX->isSelected) selected = ArrowX;
//	else if (ArrowY->isSelected) selected = ArrowY;
//	else if (ArrowZ->isSelected) selected = ArrowZ;
//	else return; 	// 기즈모의 화살표가 선택되지 않음
//
//	UArrowComponent* arrow;
//	// 마우스 델타
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
