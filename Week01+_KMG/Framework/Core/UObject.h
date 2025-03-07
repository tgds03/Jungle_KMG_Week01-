#pragma once
#include "CEngineStatics.h"
#include "CObjectMeta.h"

class UObject {
private:
	uint32 _uuid;
	uint32 _internalIndex;		// ???
public:
	UObject();
	virtual ~UObject();

	void* operator new(size_t size) {
		++CEngineStatics::TotalAllocationCount;
		//CEngineStatics::TotalAllocationBytes += size;
		return ::operator new(size);
	}

	void operator delete(void* p) {
		--CEngineStatics::TotalAllocationCount;
		//CEngineStatics::TotalAllocationBytes -= size; // ???
		free(p);
	}

	uint32 GetUUID() { return _uuid; }
	uint32 GetId() { return _internalIndex; }

	
};

// TArray		순회 가능, 상수시간에 접근, 메모리 파편화
// TLinkedList	순회 가능, On시간에 접근, 메모리 절약
// TMap			순회 가능, 상수시간에 접근
// Map을 직접 만들란 소린가?