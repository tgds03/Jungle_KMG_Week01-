#pragma once
class InputLayout {
public:
	InputLayout(ID3D11Device* device) : _device(device), _inputLayout(nullptr) {};
	~InputLayout() { 
		SafeRelease(&_inputLayout); 
	};

	ID3D11InputLayout* Get() { return _inputLayout; }

	void Create(const TArray<D3D11_INPUT_ELEMENT_DESC>& descs, ID3DBlob* vsblob);

private:
	ID3D11Device* _device;
	ID3D11InputLayout* _inputLayout;
};

