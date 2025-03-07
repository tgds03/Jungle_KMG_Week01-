#include "stdafx.h"
#include "CShader.h"

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
