#pragma once
#include "Framework/Core/UObject.h"
#include "Framework/DirectXWrapper/CBuffer.h"
#include "Framework/DirectXWrapper/CShader.h"
#include "Framework/Core/FVertexSimple.h"

class UStaticMesh : public UObject
{
public:
	UStaticMesh(const TArray<FVertexSimple>& vertices, const TArray<UINT32>& indices);
	~UStaticMesh();
private:
	TArray<FVertexSimple> Vertices;
	TArray<UINT32> Indices;

	CVertexBuffer<FVertexSimple> *VertexBuffer = nullptr;
	CIndexBuffer *IndexBuffer = nullptr;

public:
	virtual void CreateBuffer();
	CVertexBuffer<FVertexSimple>* GetVertexBuffer() const;
	CIndexBuffer* GetIndexBuffer() const;
};

