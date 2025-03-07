#include "stdafx.h"
#include "UObject.h"

TArray<UObject*> GUObjectArray;

UObject::UObject() {
	_internalIndex = GUObjectArray.size();
	GUObjectArray.push_back(this);
	_uuid = CEngineStatics::GenUUID();
}

UObject::~UObject() {
	GUObjectArray[_internalIndex] = nullptr;
}
