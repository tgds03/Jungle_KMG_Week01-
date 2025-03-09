#include "stdafx.h"
#include "UArrowComponent.h"

//#include "CRenderer.h"

ID3D11DepthStencilState* noDepthWriteState;
ID3D11DepthStencilState* previousWriteState;

UArrowComponent::UArrowComponent(EAxisColor axis) : UPrimitiveComponent(), color(axis)
{
	std::wstring filepath = L"Assets/AxisArrow.obj";
	std::ifstream objFile(filepath.c_str());
	FVector color = AxisColors[axis];


	if (objFile) {

		std::string line;
		std::vector<FVector> positions;

		while (std::getline(objFile, line)) {
			std::istringstream lineStream(line);
			std::string type;
			lineStream >> type;

			if (type == "v") // Vertex position
			{
				FVector vertex;
				lineStream >> vertex.x >> vertex.y >> vertex.z;
				FVertexSimple vertexSimple{ vertex.x, vertex.y, vertex.z, color.x,color.y,color.z, 1 };
				vertices.push_back(vertexSimple);
				positions.push_back(vertex);
			}
			else if (type == "f") // Face
			{
				std::vector<uint32_t> faceIndices;
				uint32_t index;

				while (lineStream >> index) {
					faceIndices.push_back(index - 1);
				}

				for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
					indices.push_back(faceIndices[0]);    // ù ��° ����
					indices.push_back(faceIndices[i]);    // �� ��° ����
					indices.push_back(faceIndices[i + 1]); // �� ��° ����
				}
			}

		}
	}
	CGraphics* graphics = CRenderer::Instance()->GetGraphics();
	_vertexBuffer = new CVertexBuffer<FVertexSimple>(graphics->GetDevice());
	_vertexBuffer->Create(vertices);
	_indexBuffer = new CIndexBuffer(graphics->GetDevice());
	_indexBuffer->Create(indices);
	LoadObjAndComputeBoundingBox();
}
void UArrowComponent::LoadObjAndComputeBoundingBox()
{
	std::wstring filepath = L"Assets/AxisArrowBoundBox.obj";
    std::ifstream objFile(filepath.c_str());
  

    std::string line;
    std::vector<FVector> positions;

    while (std::getline(objFile, line)) {
        std::istringstream lineStream(line);
        std::string type;
        lineStream >> type;

        if (type == "v") {
            FVector vertex;
            lineStream >> vertex.x >> vertex.y >> vertex.z;
            positions.push_back(vertex);
        }
     
    }

	for (size_t i = 1; i < positions.size(); ++i) {
		const FVector& pos = positions[i];

		minPos.x = (pos.x < minPos.x) ? pos.x : minPos.x;
		minPos.y = (pos.y < minPos.y) ? pos.y : minPos.y;
		minPos.z = (pos.z < minPos.z) ? pos.z : minPos.z;

		maxPos.x = (pos.x > maxPos.x) ? pos.x : maxPos.x;
		maxPos.y = (pos.y > maxPos.y) ? pos.y : maxPos.y;
		maxPos.z = (pos.z > maxPos.z) ? pos.z : maxPos.z;
	}
}

bool UArrowComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& Distance)
{
	FVector min = minPos;
	FVector max = maxPos;

	double tMin = -FLT_MAX;
	double tMax = FLT_MAX;
	const double epsilon = FLT_EPSILON;

	if (fabs(rayDir.x) < epsilon) {
		if (rayOrigin.x < min.x || rayOrigin.x > max.x)
			return false;
	}
	else {
		double t1 = (min.x - rayOrigin.x) / rayDir.x;
		double t2 = (max.x - rayOrigin.x) / rayDir.x;
		if (t1 > t2)
			std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	if (fabs(rayDir.y) < epsilon) {
		if (rayOrigin.y < min.y || rayOrigin.y > max.y)
			return false;
	}
	else {
		double t1 = (min.y - rayOrigin.y) / rayDir.y;
		double t2 = (max.y - rayOrigin.y) / rayDir.y;
		if (t1 > t2) std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	if (fabs(rayDir.z) < epsilon) {
		if (rayOrigin.z < min.z || rayOrigin.z > max.z)
			return false;
	}
	else
	{
		double t1 = (min.z - rayOrigin.z) / rayDir.z;
		double t2 = (max.z - rayOrigin.z) / rayDir.z;
		if (t1 > t2) std::swap(t1, t2);
		tMin = (tMin < t1) ? t1 : tMin;
		tMax = (tMax < t2) ? tMax : t2;
	}

	if (tMax >= tMin && tMax >= 0) {
		Distance = tMin;
		return true;
	}

	return false;
}

UArrowComponent::~UArrowComponent()
{
}

void UArrowComponent::Render()
{ 
	//auto d = CRenderer::Instance()->GetGraphics()->GetDevice();
	//auto dc = CRenderer::Instance()->GetGraphics()->GetDeviceContext();
	//// depth test bypass용 버퍼
	//if (noDepthWriteState == nullptr)
	//{
	//	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	//	depthStencilDesc.DepthEnable = true;
	//	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	//	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // 깊이 쓰기 X
	//	d->CreateDepthStencilState(&depthStencilDesc, &noDepthWriteState);
	//}

	//static UINT stencilRef;
	//if (color == RED_X)
	//{
	//	// 이전의 depth stencil state를 저장
	//	dc->OMGetDepthStencilState(&previousWriteState, &stencilRef);

	//	// 새로운 depth stencil state 지정
	//	dc->OMSetDepthStencilState(noDepthWriteState, 1);
	//}


	//UPrimitiveComponent::Render();


	//if (color = BLUE_Z)
	//{
	//	// depth stencil 원래대로 복원
	//	dc->OMSetDepthStencilState(previousWriteState, stencilRef);
	//}

	static bool _is_first_called = false;
	static ID3D11DepthStencilState* depthAlwaysState = nullptr;

	// 처음 호출시 override하는 뎁스 생성
	if (!_is_first_called)
	{
		CGraphics* graphics = CRenderer::Instance()->GetGraphics();
		D3D11_DEPTH_STENCIL_DESC depthDesc = {};
		depthDesc.DepthEnable = TRUE;  // Depth Test 활성화
		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;  // 항상 통과
		depthDesc.StencilEnable = FALSE;  // Stencil 사용 X
		CRenderer::Instance()->GetGraphics()->GetDevice()->CreateDepthStencilState(&depthDesc, &depthAlwaysState);

		_is_first_called = true;
	}

	static ID3D11DepthStencilState* prevDepthState = nullptr;
	static UINT prevStencilRef;

	if (color = RED_X)
	{
		CRenderer::Instance()->GetGraphics()->GetDeviceContext()->OMGetDepthStencilState(&prevDepthState, &prevStencilRef);
	}

	CRenderer::Instance()->GetGraphics()->GetDeviceContext()->OMSetDepthStencilState(depthAlwaysState, 1);

	UPrimitiveComponent::Render();

	if (color = BLUE_Z)
	{
		CRenderer::Instance()->GetGraphics()->GetDeviceContext()->OMSetDepthStencilState(prevDepthState, prevStencilRef);
		SafeRelease(&prevDepthState);

	}

}

