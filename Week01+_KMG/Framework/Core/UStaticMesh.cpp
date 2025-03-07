#include "stdafx.h"
#include "UStaticMesh.h"

UStaticMesh::UStaticMesh(TArray<FVertexSimple> vertices, TArray<UINT32> indices)
	: Vertices(vertices), Indices(indices)
{
}

UStaticMesh::~UStaticMesh()
{
	delete VertexBuffer;
	delete IndexBuffer;
}

void UStaticMesh::CreateBuffer(ID3D11Device* device)
{
	VertexBuffer = new CVertexBuffer<FVertexSimple>(device);
	VertexBuffer->Create(Vertices);
	IndexBuffer = new CIndexBuffer(device);
	IndexBuffer->Create(Indices);
}

CVertexBuffer<FVertexSimple>* UStaticMesh::GetVertexBuffer() const
{
	return VertexBuffer;
}

CIndexBuffer* UStaticMesh::GetIndexBuffer() const
{
	return IndexBuffer;
}