#include "stdafx.h"
#include "DataManager.h"
#include "UWorld.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Include/json.hpp"
DataManager* DataManager::_instance = nullptr;

bool CreateDirectoryIfNotExists(const FString& path)
{
    return CreateDirectoryA(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError();
}

void DataManager::SaveWorldToJson(UWorld* world, const FString& fileName)
{
    FString saveFileName = fileName;
    if (saveFileName.find(".Scene") == FString::npos)
        saveFileName += ".Scene";

    FString fullPath = scenePath + saveFileName;

    FString jsonData = GenerateWorldJson(world); // 월드 데이터를 json::JSON 문자열로 변환

    std::ofstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving: " << fullPath << std::endl;
        return;
    }

    file << jsonData; // json::JSON 데이터 저장
    file.close();
}

TArray<PrimitiveData> DataManager::LoadWorldFromJson(const FString& fileName)
{
    TArray<PrimitiveData> primitives;

    return primitives;
}

FString DataManager::GenerateWorldJson(UWorld* world)
{
    if (!world) return "";

    json::JSON jsonData = json::Object();


    json::JSON primitivesJson = json::Object();
    int index = 0;

    for (auto* comp : world->GetActors())
    {
        if (!comp) continue;

        UPrimitiveComponent* primitiveComp = dynamic_cast<UPrimitiveComponent*>(comp);
        if (primitiveComp == nullptr) continue;

        FVector loc = primitiveComp->GetRelativeLocation();
        FVector rot = primitiveComp->GetRelativeRotation();
        FVector scale = primitiveComp->GetRelativeScale3D();

        FString type = typeid(*primitiveComp).name();
        if (dynamic_cast<USphereComponent*>(comp)) type = "Sphere";
        else if (dynamic_cast<UCubeComponent*>(comp)) type = "Cube";
        else if (dynamic_cast<UPlaneComponent*>(comp)) type = "Plane";
        else continue;

        json::JSON primitive = json::Object();
        primitive["Location"] = SerializeFVector(loc);
        primitive["Rotation"] = SerializeFVector(rot);
        primitive["Scale"] = SerializeFVector(scale);
        primitive["Type"] = type;

        primitivesJson[std::to_string(index++)] = primitive;
    }

    jsonData["AVersion"] = 1;
    jsonData["NextUUID"] = CEngineStatics::TotalAllocationCount;
    jsonData["Primitives"] = primitivesJson;

    return jsonData.dump();
}

json::JSON DataManager::SerializeFVector(const FVector& vec)
{
    return json::JSON();
}


//FVector DataManager::DeserializeFVector(const json::JSON& jsonArray)
//{
//    //return FVector(jsonArray[0].ToFloat(), jsonArray[1].ToFloat(), jsonArray[2].ToFloat());
//}