#pragma once
#include "USceneComponent.h"
#include "./Framework/DirectXWrapper/CBuffer.h"
#include "./Framework/DirectXWrapper/CInputLayout.h"

class UPrimitiveComponent: public USceneComponent {
public:
	TArray<FVertexSimple> vertices;
	TArray<uint32> indices;
	FString type;

	virtual void Render();
protected:
	CVertexBuffer<FVertexSimple>* _vertexBuffer;
	CIndexBuffer* _indexBuffer;
};