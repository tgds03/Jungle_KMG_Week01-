#include "stdafx.h"
#include "AActor.h"
#include "Framework/Core/UPrimitiveComponent.h"

TLinkedList<AActor*> GAActorList;

AActor::AActor() {
	GAActorList.push_back(this);
}

AActor::~AActor() {
	GAActorList.remove(this);
}

void AActor::OnRegister(UActorComponent* component) {
	_components.push_back(component);
}

void AActor::OnUnregister(UActorComponent* component) {
	_components.remove(component);
}

void AActor::Update() {
	for(auto comp: _components) {
		comp->Update();
	}
}

void AActor::Render() {
	for ( auto comp : _components ) {
		if (UPrimitiveComponent* renderable = dynamic_cast<UPrimitiveComponent*>(comp))
		{
			renderable->Render();
		}
	}
}
