#pragma once

#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <assert.h>
#include "comdef.h"
#include <Windows.h>

#include <vector>
#include <list>
#include <string>
template <typename T> using TArray = std::vector<T>;
template <typename T> using TLinkedList = std::list<T>;
using int32 = int;
using uint32 = unsigned int;
using FString = std::string;
using FWString = std::wstring;

#include "Math/FVector.h"
#include "Math/FMatrix.h"
#define M_PI           3.14159265358979323846

#define SCR_WIDTH 1200
#define SCR_HEIGHT 800


#include "Framework/Core/Time.h"
#include "Framework/Core/Input.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "GuiController.h"

template <typename T> void SafeRelease(T** ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = nullptr;
	}
}


#define UE_LOG OutputDebugString

inline float degToRad(float deg) { return deg * M_PI / 180.f; }
inline float radToDeg(float rad) { return rad * 180.f / M_PI; }