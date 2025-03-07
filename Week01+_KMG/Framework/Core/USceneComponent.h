#pragma once
#include "Framework/Core/UActorComponent.h"
class USceneComponent :public UActorComponent {

// 물리, 변환 관련
private:
	FVector RelativeLocation;
	FVector RelatvieRotation;
	FVector RelativeScale3D;
	FVector ComponentVelocity;

public:
	FVector GetRelativeLocation() const;
	FVector GetRelativeRotation() const;
	FVector GetRelativeScale3D() const; 
	FVector GetComponentVelocity() const;

	void SetRelativeLocation(_In_ FVector Location);
	void SetRelativeRotation(_In_ FVector Rotation);
	void SetRelativeScale3D(_In_ FVector Scale3D);
	void SetComponentVelocity(_In_ FVector Velocity);

// 상속 관련
private:
	USceneComponent* AttachParent = nullptr;
	TArray<USceneComponent*> AttachChildern;

public:
	const TArray<USceneComponent*>& GetAttachChildren() const; // 직접적으로 붙은 children만 반환
	void GetChildrenComponents(_Out_ TArray<USceneComponent*>& Children) const; // 재귀로 아래의 모든 children 반환
	USceneComponent* GetAttachParent() const;
	void GetParentComponents(_Out_ TArray<USceneComponent*>& Parents) const; // 재귀로 root까지 반환
	
	void SetupAttachment(_In_ TArray<USceneComponent*>& Children); // 자식 설정 실패 가능

	// 부모자식 관계를 실제로 정하는 이 함수 뿐임
	bool AttachToComponent(_In_ USceneComponent* Parent); // 부모 설정 실패했을땐 false

	// **자식 추가하는 함수는 금지; AttachToComponent 사용해야함**
	//void AttachChildren(_In_ USceneComponent* Child);
	//void SetAttachParent(_In_ USceneComponent* Parent);
};

// 테스트용 코드
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