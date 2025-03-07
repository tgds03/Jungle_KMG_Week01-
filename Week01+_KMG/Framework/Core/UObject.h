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

// TArray		��ȸ ����, ����ð��� ����, �޸� ����ȭ
// TLinkedList	��ȸ ����, On�ð��� ����, �޸� ����
// TMap			��ȸ ����, ����ð��� ����
// Map�� ���� ����� �Ҹ���?