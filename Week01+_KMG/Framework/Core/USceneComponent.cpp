#include "stdafx.h"
#include "USceneComponent.h"

void USceneComponent::Update()
{
	UActorComponent::Update();
}

FVector USceneComponent::Right() {
	FVector4 r = GetComponentTransform().r1();
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Up() {
	FVector4 r = GetComponentTransform().r2();
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Front() {
	FVector4 r = GetComponentTransform().r3();
	return FVector(r.x, r.y, r.z).Normalized();
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
	//FMatrix origin = FMatrix(FVector4::Zero, FVector4::Zero, FVector4::Zero, FVector4(0, 0, 0, 1));
	FMatrix origin = FMatrix::Identity;

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

void USceneComponent::SetRelativeLocation(const FVector NewLocation)
{
	RelativeLocation = NewLocation;
}

void USceneComponent::SetRelativeLocationX(const float NewLocX)
{
	RelativeLocation.x = NewLocX;
}

void USceneComponent::SetRelativeLocationY(const float NewLocY)
{
	RelativeLocation.y = NewLocY;
}

void USceneComponent::SetRelativeLocationZ(const float NewLocZ)
{
	RelativeLocation.z = NewLocZ;
}

void USceneComponent::SetRelativeRotation(const FVector NewRotation)
{
	RelativeRotation = NewRotation;
}

void USceneComponent::SetRelativeRotationX(const float NewRotX)
{
	RelativeRotation.x = NewRotX;
}

void USceneComponent::SetRelativeRotationY(const float NewRotY)
{
	RelativeRotation.y = NewRotY;
}

void USceneComponent::SetRelativeRotationZ(const float NewRotZ)
{
	RelativeRotation.z = NewRotZ;
}

void USceneComponent::SetRelativeScale3D(const FVector NewScale3D)
{
	RelativeScale3D = NewScale3D;
}

void USceneComponent::SetRelativeScale3DX(const float NewScaleX)
{
	RelativeScale3D.x = NewScaleX;
}

void USceneComponent::SetRelativeScale3DY(const float NewScaleY)
{
	RelativeScale3D.y = NewScaleY;
}

void USceneComponent::SetRelativeScale3DZ(const float NewScaleZ)
{
	RelativeScale3D.z = NewScaleZ;
}

// ���� ��ǥ���� �ű��, ���� Parent���� �����ġ�� �̿� ���� ������Ʈ
void USceneComponent::SetWorldLocation(const FVector NewWorldLocation)
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

void USceneComponent::SetWorldRotation(const FVector NewWorldRotation)
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

void USceneComponent::SetWorldLocationAndRotation(const FVector NewWorldLocation)
{
	FMatrix invTrans = GetAttachParent()->GetComponentTransform().Inverse();
	SetRelativeLocation((GetRelativeLocation4() * invTrans).xyz());
	SetRelativeRotation((FVector4(GetRelativeRotation(), 0) * invTrans).xyz());
}

//void USceneComponent::SetWorldScale3D(const FVector NewWorldScale3D)
//{
//
//}

// const�� pass by reference(&)
// �����͸� ȿ�������� �����ϸ鼭 ȣ���� �Լ��� �� ������Ʈ�� children�� �ٲ��� ���ϰ� ��
// ���� ���� �ٸ� ������ �ű����("=" operator) ���
const TArray<USceneComponent*>& USceneComponent::GetAttachChildren() const
{
	return AttachChildern;
}

void USceneComponent::GetChildrenComponents(TArray<USceneComponent*>& Children) const
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

void USceneComponent::GetParentComponents(TArray<USceneComponent*>& Parents) const
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
void USceneComponent::SetupAttachment(TArray<USceneComponent*>& Children)
{
	AttachChildern.clear();

	for (auto& child : Children)
	{
		if (!child->AttachToComponent(this))
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

bool USceneComponent::AttachToComponent(USceneComponent* Parent)
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

void USceneComponent::PrintLoc(std::wstring msg) const
{
	FVector loc = GetRelativeLocation();
	UE_LOG((std::wstring(L"\n") + msg + std::wstring(L"*************************\n")).c_str());
	UE_LOG((std::wstring(L"Relative Location\nx :") + std::to_wstring(loc.x) + std::wstring(L" y :")
		+ std::to_wstring(loc.y) + std::wstring(L" z :") + std::to_wstring(loc.z) + std::wstring(L"\n")).c_str());
	loc = GetComponentLocation();
	UE_LOG((std::wstring(L"Component Location\nx :") + std::to_wstring(loc.x) + std::wstring(L" y :")
		+ std::to_wstring(loc.y) + std::wstring(L" z :") + std::to_wstring(loc.z) + std::wstring(L"\n")).c_str());
}

