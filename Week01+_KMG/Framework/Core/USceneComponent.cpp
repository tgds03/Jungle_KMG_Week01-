#include "stdafx.h"
#include "USceneComponent.h"

void USceneComponent::Update()
{
	UActorComponent::Update();
}

//void USceneComponent::Render()
//{
//	UActorComponent::Render();
//}

FVector USceneComponent::GetRelativeLocation() const
{
	return RelativeLocation;
}

FVector4 USceneComponent::GetRelativeLocation4() const
{
	return FVector4(RelativeLocation, 1);
}

FVector USceneComponent::GetRelativeRotation() const
{
	return RelativeRotation;
}

FVector USceneComponent::GetRelativeScale3D() const
{
	return RelativeScale3D;
}

FMatrix USceneComponent::GetRelativeTransform() const
{
	FMatrix origin = FMatrix(FVector4::Zero, FVector4::Zero, FVector4::Zero, FVector4(0, 0, 0, 1));

	FMatrix scale = FMatrix::Scale(RelativeScale3D);
	FMatrix rot = FMatrix::RotateX(RelativeRotation.x) * FMatrix::RotateY(RelativeRotation.y) * FMatrix::RotateZ(RelativeRotation.z);
	FMatrix trans = FMatrix::Translate(RelativeLocation);

	return origin * scale * rot * trans;
}

FVector USceneComponent::GetComponentLocation() const
{
	if (AttachParent != nullptr)
	{
		FVector4 componentVec = (FVector4(GetRelativeLocation(), 1) * AttachParent->GetComponentTransform());
		return FVector(componentVec.xyz() / componentVec.w);
	}
	else
	{
		return GetRelativeLocation();
	}
}

//FVector USceneComponent::GetComponentRotation() const
//{
//	if (AttachParent != nullptr)
//	{
//		return FVector((FVector4(GetRelativeRotation(), 0) * AttachParent->GetComponentTransform()).xyz());
//	}
//	else
//	{
//		return GetRelativeRotation();
//	}
//}
//
//FVector USceneComponent::GetComponentScale() const
//{
//	if (AttachParent != nullptr)
//	{
//		return FVector((FVector4(GetRelativeScale3D(), 0) * AttachParent->GetComponentTransform()).xyz());
//	}
//	else
//	{
//		return GetRelativeScale3D();
//	}
//}
FMatrix USceneComponent::GetComponentTransform() const
{
	if (AttachParent != nullptr)
	{
		return GetRelativeTransform() * AttachParent->GetComponentTransform();
	}
	else
	{
		return GetRelativeTransform();
	}
}

void USceneComponent::SetRelativeLocation(_In_ const FVector NewLocation)
{
	RelativeLocation = NewLocation;
}

void USceneComponent::SetRelativeRotation(_In_ const FVector NewRotation)
{
	RelativeRotation = NewRotation;
}

void USceneComponent::SetRelativeScale3D(_In_ const FVector NewScale3D)
{
	RelativeScale3D = NewScale3D;
}

// 월드 좌표에서 옮기고, 이후 Parent와의 상대위치를 이에 따라 업데이트
void USceneComponent::SetWorldLocation(_In_ const FVector NewWorldLocation)
{ 
	if (GetAttachParent() != nullptr)
	{
		SetRelativeLocation((GetRelativeLocation4() * GetAttachParent()->GetComponentTransform().Inverse()).xyz());
	}
	else
	{
		SetRelativeLocation(NewWorldLocation);
	}
}

void USceneComponent::SetWorldRotation(_In_ const FVector NewWorldRotation)
{
	if (GetAttachParent() != nullptr)
	{
		SetRelativeRotation((FVector4(GetRelativeRotation(), 0) * GetAttachParent()->GetComponentTransform().Inverse()).xyz());
	}
	else
	{
		SetRelativeLocation(NewWorldRotation);
	}
}

void USceneComponent::SetWorldLocationAndRotation(_In_ const FVector NewWorldLocation)
{
	FMatrix invTrans = GetAttachParent()->GetComponentTransform().Inverse();
	SetRelativeLocation((GetRelativeLocation4() * invTrans).xyz());
	SetRelativeRotation((FVector4(GetRelativeRotation(), 0) * invTrans).xyz());
}

//void USceneComponent::SetWorldScale3D(_In_ const FVector NewWorldScale3D)
//{
//
//}

// const랑 pass by reference(&)
// 데이터를 효율적으로 전달하면서 호출한 함수가 이 오브젝트의 children을 바꾸지 못하게 함
// 리턴 값을 다른 변수에 옮기고서("=" operator) 사용
const TArray<USceneComponent*>& USceneComponent::GetAttachChildren() const
{
	return AttachChildern;
}

void USceneComponent::GetChildrenComponents(_Out_ TArray<USceneComponent*>& Children) const
{
	Children.clear();
	for (auto& child : Children)
	{
		TArray<USceneComponent*> childComponents;
		child->GetChildrenComponents(childComponents);
		Children.insert(Children.end(), childComponents.begin(), childComponents.end());
	}
}

USceneComponent* USceneComponent::GetAttachParent() const
{
	return AttachParent;
}

void USceneComponent::GetParentComponents(_Out_ TArray<USceneComponent*>& Parents) const
{
	Parents.clear();

	// 언리얼 소스코드 /Engine/Source/Runtime/Engine/Classes/Components/SceneComponent.h 참고
	USceneComponent* ParentIterator = GetAttachParent();
	while (ParentIterator != nullptr)
	{
		Parents.push_back(ParentIterator);
		ParentIterator = ParentIterator->GetAttachParent();
	}
}

// pass by reference로 메모리 절약
void USceneComponent::SetupAttachment(_In_ TArray<USceneComponent*>& Children)
{
	AttachChildern.clear();

	for (auto& child : Children)
	{
		if (child->AttachToComponent(this))
		{
			UE_LOG(L"USceneComponent::SetupAttachment::Children으로 지정하는데 실패했습니다.");
		}
	}
}

//void USceneComponent::AttachChildren(USceneComponent* Child)
//{
//	if (Child == this)
//	{
//		UE_LOG(L"자기 자신을 Children으로 할 수 없습니다.");
//		return;
//	}
//	TArray<USceneComponent*> parents;
//	GetParentComponents(parents);
//	for (auto& parent : parents)
//	{
//		if (this == parent->GetAttachParent()) {
//			UE_LOG(L"Ancestor를 Children으로 할 수 없습니다.");
//			return;
//		}
//	}
//	AttachChildern.push_back(Child);
//}

bool USceneComponent::AttachToComponent(_In_ USceneComponent* Parent)
{
	if (Parent == this)
	{
		UE_LOG(L"USceneComponent::AttachToComponent::자기 자신을 Parent로 할 수 없습니다.");
		return false;
	}

	// parent로 하려는 컴포넌트의 조상에 *this가 있는지 확인
	TArray<USceneComponent*> parentsOfInput;
	Parent->GetParentComponents(parentsOfInput);
	if (parentsOfInput.end() != std::find(parentsOfInput.begin(), parentsOfInput.end(), this))
	{
		UE_LOG(L"USceneComponent::AttachToComponent::Descendent를 Parent로 할 수 없습니다.");
		return false;
	}

	Parent->AttachChildern.push_back(Parent);
	AttachParent = Parent;
	return true;

	//TArray<USceneComponent*> children;
	//GetChildrenComponents(children);
	//if (children.end() != std::find(children.begin(), children.end(), this))
	//{

	//}
	//return true;
}

