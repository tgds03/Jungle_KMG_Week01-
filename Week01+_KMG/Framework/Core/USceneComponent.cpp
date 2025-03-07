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

// ���� ��ǥ���� �ű��, ���� Parent���� �����ġ�� �̿� ���� ������Ʈ
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

// const�� pass by reference(&)
// �����͸� ȿ�������� �����ϸ鼭 ȣ���� �Լ��� �� ������Ʈ�� children�� �ٲ��� ���ϰ� ��
// ���� ���� �ٸ� ������ �ű��("=" operator) ���
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

	// �𸮾� �ҽ��ڵ� /Engine/Source/Runtime/Engine/Classes/Components/SceneComponent.h ����
	USceneComponent* ParentIterator = GetAttachParent();
	while (ParentIterator != nullptr)
	{
		Parents.push_back(ParentIterator);
		ParentIterator = ParentIterator->GetAttachParent();
	}
}

// pass by reference�� �޸� ����
void USceneComponent::SetupAttachment(_In_ TArray<USceneComponent*>& Children)
{
	AttachChildern.clear();

	for (auto& child : Children)
	{
		if (child->AttachToComponent(this))
		{
			UE_LOG(L"USceneComponent::SetupAttachment::Children���� �����ϴµ� �����߽��ϴ�.");
		}
	}
}

//void USceneComponent::AttachChildren(USceneComponent* Child)
//{
//	if (Child == this)
//	{
//		UE_LOG(L"�ڱ� �ڽ��� Children���� �� �� �����ϴ�.");
//		return;
//	}
//	TArray<USceneComponent*> parents;
//	GetParentComponents(parents);
//	for (auto& parent : parents)
//	{
//		if (this == parent->GetAttachParent()) {
//			UE_LOG(L"Ancestor�� Children���� �� �� �����ϴ�.");
//			return;
//		}
//	}
//	AttachChildern.push_back(Child);
//}

bool USceneComponent::AttachToComponent(_In_ USceneComponent* Parent)
{
	if (Parent == this)
	{
		UE_LOG(L"USceneComponent::AttachToComponent::�ڱ� �ڽ��� Parent�� �� �� �����ϴ�.");
		return false;
	}

	// parent�� �Ϸ��� ������Ʈ�� ���� *this�� �ִ��� Ȯ��
	TArray<USceneComponent*> parentsOfInput;
	Parent->GetParentComponents(parentsOfInput);
	if (parentsOfInput.end() != std::find(parentsOfInput.begin(), parentsOfInput.end(), this))
	{
		UE_LOG(L"USceneComponent::AttachToComponent::Descendent�� Parent�� �� �� �����ϴ�.");
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

