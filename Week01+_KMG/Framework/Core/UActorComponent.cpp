#include "stdafx.h"
#include "UPrimitiveComponent.h"

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
		if (UPrimitiveComponent* drawable = dynamic_cast<UPrimitiveComponent*>(comp))
		{
			drawable->Render();
		}
	}
}


