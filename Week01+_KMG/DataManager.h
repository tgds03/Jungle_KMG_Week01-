#pragma once
#include "stdafx.h"
#include "Framework/Core/CEngineStatics.h"

class UWorld;
struct Primitives;

class DataManager
{
public:
	static DataManager* Instance() 
	{
		if (_instance == nullptr)
			_instance = new DataManager();
		return _instance;
	};

	static void Release() 
	{
		delete _instance;
		_instance = nullptr;
	}

	void SaveWorldToJson(UWorld* world, const FString& fileName);
	TArray<PrimitiveData> LoadWorldFromJson(const FString& fileName);

	FString GenerateWorldJson(UWorld* world);

private:
	DataManager() = default;
	~DataManager() = default;
	// Safe code for Singleton
	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;

	

	static DataManager* _instance;
	const FString scenePath = "Scenes/";
};
