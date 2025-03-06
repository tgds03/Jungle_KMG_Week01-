#include "stdafx.h"
#include "CInputLayout.h"

void InputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& descs, ID3DBlob* vsblob) {
	const uint32 count = static_cast<uint32>(descs.size());
	HRESULT hr = _device->CreateInputLayout(descs.data(), count, vsblob->GetBufferPointer(), vsblob->GetBufferSize(), &_inputLayout);
}
