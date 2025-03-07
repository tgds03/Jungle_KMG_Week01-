#pragma once
#include "Framework/Core/UActorComponent.h"

// ���� : �Լ��̸��� Component�� ������ ��������� ���/ȣ����

class USceneComponent :public UActorComponent {
public:
	virtual void Update();
	virtual void Render();

	// ������ ����
private:
	bool bVisible = true;
public:
	void setVisible(const bool bValue);

// ����, ��ȯ ����
private:
	// ����ȭ ��� ��Ű��
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D;
	//FVector ComponentVelocity;
	FMatrix ComponentToWorld;

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

	void SetRelativeLocation(_In_ const FVector NewLocation);
	void SetRelativeRotation(_In_ const FVector NewRotation);
	void SetRelativeScale3D(_In_ const FVector NewScale3D);
	//void SetComponentVelocity(_In_ const FVector NewVelocity);

	void SetWorldLocation(_In_ const FVector NewWorldLocation);
	void SetWorldRotation(_In_ const FVector NewWorldRotation);
	void SetWorldLocationAndRotation(_In_ const FVector NewWorldLocation);
	//void SetWorldScale3D(_In_ const FVector NewWorldScale3D);
	//void SetWorldVelocity(_In_ const FVector NewWorldVelocity);

	//void UpdateComponentVelocity();

// ��� ����
private:
	USceneComponent* AttachParent = nullptr;
	TArray<USceneComponent*> AttachChildern;

public:
	const TArray<USceneComponent*>& GetAttachChildren() const; // ���������� ���� children�� ��ȯ
	void GetChildrenComponents(_Out_ TArray<USceneComponent*>& Children) const; // ��ͷ� �Ʒ��� ��� children ��ȯ
	USceneComponent* GetAttachParent() const;
	void GetParentComponents(_Out_ TArray<USceneComponent*>& Parents) const; // ��ͷ� root���� ��ȯ
	
	void SetupAttachment(_In_ TArray<USceneComponent*>& Children); // �ڽ� ���� ���� ����

	// �θ��ڽ� ���踦 ������ ���ϴ� �� �Լ� ����
	bool AttachToComponent(_In_ USceneComponent* Parent); // �θ� ���� ���������� false

	// **�ڽ� �߰��ϴ� �Լ��� ����; AttachToComponent ����ؾ���**
	//void AttachChildren(_In_ USceneComponent* Child);
	//void SetAttachParent(_In_ USceneComponent* Parent);
};

// �׽�Ʈ�� �ڵ�
//USceneComponent* s1, * s2, * s3, * s4, * s5;
//s1 = new USceneComponent;
//s2 = new USceneComponent;
//s3 = new USceneComponent;
//s4 = new USceneComponent;
//s5 = new USceneComponent;
//
//s5->AttachToComponent(s4);
//s4->AttachToComponent(s2);
//s3->AttachToComponent(s2);
//s2->AttachToComponent(s1);
//
//int res = s5->AttachToComponent(s3);