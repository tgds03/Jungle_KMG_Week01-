#include "stdafx.h"
#include "UActorComponent.h"

TLinkedList<UActorComponent*> GUActorComponentList;

UActorComponent::UActorComponent() {
	GUActorComponentList.push_back(this);
}

UActorComponent::~UActorComponent() {
	GUActorComponentList.remove(this);
}
