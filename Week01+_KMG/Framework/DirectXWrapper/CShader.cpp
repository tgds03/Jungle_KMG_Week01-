#include "stdafx.h"
#include "CShader.h"
#include <comdef.h>

void CShader::LoadShaderFromFile(const FWString& path, const FString& name, const FString& version) {
	_path = path;
	_name = name;
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	HRESULT hr = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		&_blob,
		nullptr
	);
	if (!SUCCEEDED(hr))
	{
		_com_error err(hr);
		std::wstring errMsg = err.ErrorMessage();
		// HRESULT 값도 함께 출력 (16진수 형식으로 보기 쉽게)
		wchar_t debugMsg[512];
		swprintf_s(debugMsg, L"Error: 0x%08X - %s\n", hr, errMsg.c_str());
		OutputDebugString(debugMsg);
	}
	assert(SUCCEEDED(hr));
}

void CVertexShader::Create(const FWString& path, const FString& name, const FString& version) {
	LoadShaderFromFile(path, name, version);
	HRESULT hr = _device->CreateVertexShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, &_vertexShader);
	assert(SUCCEEDED(hr));
}

void CPixelShader::Create(const FWString& path, const FString& name, const FString& version) {
	LoadShaderFromFile(path, name, version);
	HRESULT hr = _device->CreatePixelShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, &_pixelShader);
	assert(SUCCEEDED(hr));
}
