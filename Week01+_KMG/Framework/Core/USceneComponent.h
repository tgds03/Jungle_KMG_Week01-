#pragma once
#include "Framework/Core/UActorComponent.h"

// 참고 : 함수이름에 Component가 있으면 재귀적으로 계산/호출함

class USceneComponent :public UActorComponent {
public:
	virtual void Update();
	virtual void Render();

	// 렌더링 관련
private:
	bool bVisible = true;
public:
	void setVisible(const bool bValue);

// 물리, 변환 관련
private:
	// 동기화 어떻게 시키지
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