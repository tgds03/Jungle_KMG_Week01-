#pragma once
#include "stdafx.h"
#include "Framework/Core/CEngineStatics.h"
#include "Framework/Core/CObjectMeta.h"
#include <unordered_map>

class UObject {
private:
	uint32 _uuid;
	uint32 _internalIndex;		// ???
	static std::unordered_map<void*, size_t> _allocationMap;
public:
	UObject();
	virtual ~UObject();

	void* operator new(size_t size) {
		void* ptr = ::operator new(size);
		++CEngineStatics::TotalAllocationCount;
		_allocationMap[ptr] = size;
		CEngineStatics::TotalAllocationBytes += size;
		return ptr;
	}

	void operator delete(void* p) {
		--CEngineStatics::TotalAllocationCount;
		CEngineStatics::TotalAllocationBytes -= _allocationMap[p];
		_allocationMap.erase(p);
		free(p);
	}

	uint32 GetUUID() { return _uuid; }
	uint32 GetId() { return _internalIndex; }

	
};

// TArray		��ȸ ����, ����ð��� ����, �޸� ����ȭ
// TLinkedList	��ȸ ����, On�ð��� ����, �޸� ����
// TMap			��ȸ ����, ����ð��� ����
// Map�� ���� ����� �Ҹ���?