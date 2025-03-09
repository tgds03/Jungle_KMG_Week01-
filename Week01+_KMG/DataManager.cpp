#include "stdafx.h"
#include "DataManager.h"
#include "UWorld.h"
//#include "UPrimitiveComponent.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

DataManager* DataManager::_instance = nullptr;

bool CreateDirectoryIfNotExists(const FString& path)
{
    //#ifdef _WIN32
    return CreateDirectoryA(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError();
    //#else
    //	struct stat info;
    //	if (stat(path.c_str(), &info) != 0) {
    //		return mkdir(path.c_str(), 0777) == 0;
    //	}
    //	return (info.st_mode & S_IFDIR) != 0;
    //#endif
}

void DataManager::SaveWorldToJson(UWorld* world, const FString& fileName)
{
    if (!world) return;

    FString saveFileName = fileName;

    // 확장자가 없거나 다른 확장자인 경우 자동으로 .Scene 추가
    if (saveFileName.find(".Scene") == FString::npos)
        saveFileName += ".Scene";

    FString fullPath = scenePath + saveFileName;
    if (!CreateDirectoryIfNotExists(scenePath))
    {
        std::cerr << "Failed to create directory: " << scenePath << std::endl;
        return;
    }

    FString jsonString = GenerateWorldJson(world);

    std::ofstream file(fullPath);
    if (!file.is_open()) return;

    file << jsonString;
    file.close();
}

//FString DataManager::LoadWorldFromJson(UWorld* world, const FString& fileName)
//{
//    if (!world) return;
//
//    FString loadFileName = fileName;
//
//    if (loadFileName.find(".Scene") == FString::npos)
//        loadFileName += ".Scene";
//
//    FString fullPath = scenePath + loadFileName;
//
//    std::ifstream file(fullPath);
//    if (!file.is_open())
//    {
//        return;
//    }
//
//    std::stringstream buffer;
//    buffer << file.rdbuf();
//    file.close();
//
//    FString content = buffer.str();
//}

TArray<PrimitiveData> DataManager::LoadWorldFromJson(const FString& fileName)
{
    TArray<PrimitiveData> primitives;

    FString loadFileName = fileName;
    if (loadFileName.find(".Scene") == FString::npos)
        loadFileName += ".Scene";

    FString fullPath = scenePath + loadFileName;

    std::ifstream file(fullPath);
    if (!file.is_open())
    {
        std::cerr << "File not found: " << fullPath << std::endl;
        return primitives;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    FString content = buffer.str();

    int32 index = 0;

    return primitievs;
}

FString DataManager::GenerateWorldJson(UWorld* world)
{
    if (!world) return "";

    std::ostringstream json;
    json << "{\n";
    json << "  \"Version\" : 1,\n";
    json << "  \"NextUUID\" : " << CEngineStatics::TotalAllocationCount << ",\n";
    json << "  \"Primitives\" : {\n";

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

        json << "    \"" << index++ << "\" : {\n";
        json << "      \"Location\" : [" << loc.x << ", " << loc.y << ", " << loc.z << "],\n";
        json << "      \"Rotation\" : [" << rot.x << ", " << rot.y << ", " << rot.z << "],\n";
        json << "      \"Scale\" : [" << scale.x << ", " << scale.y << ", " << scale.z << "],\n";
        json << "      \"Type\" : \"" << type << "\"\n";
        json << "    }" << (index < world->GetActorCount() ? "," : "") << "\n";
    }

    json << "  }\n";
    json << "}\n";

    return json.str();
}

TArray<float> ParseFloatArray(const FString& json, const FString& key) 
{
    TArray<float> result;
    size_t start = json.find(key);
    if (start == FString::npos) return result;

    start = json.find("[", start);
    if (start == FString::npos) return result;

    size_t end = json.find("]", start);
    if (end == FString::npos) return result;

    FString arrayStr = json.substr(start + 1, end - start - 1);
    std::stringstream ss(arrayStr);
    FString num;

    while (getline(ss, num, ',')) 
    {
        result.push_back(std::stof(num));
    }

    return result;
}

FString ParseString(const FString& json, const FString& key)
{
    size_t start = json.find(key);
    if (start == FString::npos) return "";

    start = json.find("\"", start + key.length());
    size_t end = json.find("\"", start + 1);
    if (start == FString::npos || end == FString::npos) return "";

    return json.substr(start + 1, end - start - 1);
}