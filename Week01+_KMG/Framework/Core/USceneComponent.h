#pragma once
#include "Framework/Core/UActorComponent.h"
class USceneComponent :public UActorComponent {

// 물리, 변환 관련
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
