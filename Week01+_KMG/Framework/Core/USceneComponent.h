#pragma once
#include "Framework/Core/UActorComponent.h"
class USceneComponent :public UActorComponent {
public:
	USceneComponent() {}
	virtual void Update();
	//virtual void Render();
public:
	FVector RelativeLocation = FVector::Zero;
	FVector RelativeRotation = FVector::Zero;
	FVector RelativeScale3D = FVector::One;

	//FMatrix Transformation();

public:
	FVector GetRelativeLocation() const;
	FVector4 GetRelativeLocation4() const;
	FVector GetRelativeRotation() const;
	FVector GetRelativeScale3D() const;
	FMatrix GetRelativeTransform() const;

	FVector GetComponentLocation() const;
	//FVector GetComponentRotation() const;
	//FVector GetComponentScale() const;
	FMatrix GetComponentTransform() const;
	//FVector GetComponentVelocity() const;

	void SetRelativeLocation(const FVector NewLocation);
	void SetRelativeLocationX(const float NewLocX);
	void SetRelativeLocationY(const float NewLocY);
	void SetRelativeLocationZ(const float NewLocZ);
	void SetRelativeRotation(const FVector NewRotation);
	void SetRelativeRotationX(const float NewRotX);
	void SetRelativeRotationY(const float NewRotY);
	void SetRelativeRotationZ(const float NewRotZ);
	void SetRelativeScale3D(const FVector NewScale3D);
	void SetRelativeScale3DX(const float NewScaleX);
	void SetRelativeScale3DY(const float NewScaleY);
	void SetRelativeScale3DZ(const float NewScaleZ);
	//void SetComponentVelocity(const FVector NewVelocity);

	void SetWorldLocation(const FVector NewWorldLocation);
	void SetWorldRotation(const FVector NewWorldRotation);
	void SetWorldLocationAndRotation(const FVector NewWorldLocation);
	//void SetWorldScale3D(const FVector NewWorldScale3D);
	//void SetWorldVelocity(const FVector NewWorldVelocity);

	//void UpdateComponentVelocity();

// ��� ����
protected:
	USceneComponent* AttachParent = nullptr;
	TArray<USceneComponent*> AttachChildern;

public:
	const TArray<USceneComponent*>& GetAttachChildren() const; // ���������� ���� children�� ��ȯ
	void GetChildrenComponents(TArray<USceneComponent*>& Children) const; // ��ͷ� �Ʒ��� ��� children ��ȯ
	USceneComponent* GetAttachParent() const;
	void GetParentComponents(TArray<USceneComponent*>& Parents) const; // ��ͷ� root���� ��ȯ

	void SetupAttachment(TArray<USceneComponent*>& Children); // �ڽ� ���� ���� ����

	// �θ��ڽ� ���踦 ������ ���ϴ� �� �Լ� ����
	bool AttachToComponent(USceneComponent* Parent); // �θ� ���� ���������� false

// �����
public:
	void PrintLoc(std::wstring msg) const;
};

