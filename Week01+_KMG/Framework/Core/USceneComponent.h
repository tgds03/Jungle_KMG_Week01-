#pragma once
#include "Framework/Core/UActorComponent.h"
class USceneComponent :public UActorComponent {

// ����, ��ȯ ����
private:
	FVector4 RelativeLocation;
	FVector4 RelatvieRotation;
	FVector4 RelativeScale3D;
	FVector4 ComponentVelocity;

public:
	FVector4 GetRelativeLocation() const;
	FVector4 GetRelativeRotation() const;
	FVector4 GetRelativeScale3D() const; 
	FVector4 GetComponentVelocity() const;

	void SetRelativeLocation(_In_ FVector4 Location);
	void SetRelativeRotation(_In_ FVector4 Rotation);
	void SetRelativeScale3D(_In_ FVector4 Scale3D);
	void SetComponentVelocity(_In_ FVector4 Velocity);

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