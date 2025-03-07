#include "stdafx.h"
#include "USceneComponent.h"

FVector USceneComponent::GetRelativeLocation() const
{
	return RelativeLocation;
}

FVector USceneComponent::GetRelativeRotation() const
{
	return RelatvieRotation;
}

FVector USceneComponent::GetRelativeScale3D() const
{
	return RelativeScale3D;
}

FVector USceneComponent::GetComponentVelocity() const
{
	return ComponentVelocity;
}

void USceneComponent::SetRelativeLocation(_In_ FVector Location)
{
	RelativeLocation = Location;
}

void USceneComponent::SetRelativeRotation(_In_ FVector Rotation)
{
	RelatvieRotation = Rotation;
}

void USceneComponent::SetRelativeScale3D(_In_ FVector Scale3D)
{
	RelativeScale3D = Scale3D;
}

void USceneComponent::SetComponentVelocity(_In_ FVector Velocity)
{
	ComponentVelocity = Velocity;
}

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

