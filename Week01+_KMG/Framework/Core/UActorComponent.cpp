#include "stdafx.h"
#include "UActorComponent.h"

TLinkedList<UActorComponent*> GUActorComponentList;

UActorComponent::UActorComponent() {
	GUActorComponentList.push_back(this);
}

UActorComponent::~UActorComponent() {
	GUActorComponentList.remove(this);
}

void UActorComponent::UpdateAll() {
	for(auto comp: GUActorComponentList) {
		comp->Update();
	}
}

void UActorComponent::RenderAll() {
	for ( auto comp : GUActorComponentList ) {
		comp->Render();
	}
}

void UActorComponent::GenerateAllRayForPicking(FVector& pickPosition, FMatrix& viewMatrix)
{
	for (auto comp : GUActorComponentList) {
		FVector rayOrigin, rayDir;
		comp->GenerateRayForPicking(pickPosition, viewMatrix, &rayOrigin, &rayDir);
	}
}


