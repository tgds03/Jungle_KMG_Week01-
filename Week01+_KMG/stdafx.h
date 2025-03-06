#pragma once

#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <assert.h>
#include <Windows.h>

#include <vector>
#include <list>
template <typename T> using TArray = std::vector<T>;
template <typename T> using TLinkeList = std::list<T>;