#include "stdafx.h"
#include "UArrowComponent.h"

UArrowComponent::UArrowComponent(EAxisColor axis): UPrimitiveComponent()
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
					indices.push_back(faceIndices[0]);    // 첫 번째 정점
					indices.push_back(faceIndices[i]);    // 두 번째 정점
					indices.push_back(faceIndices[i + 1]); // 세 번째 정점
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

