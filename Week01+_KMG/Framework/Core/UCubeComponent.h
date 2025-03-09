#pragma once
#include "./Framework/Core/UPrimitiveComponent.h"
class UCubeComponent: public UPrimitiveComponent {
public:
	UCubeComponent();
	virtual ~UCubeComponent();
	virtual void Update();
	virtual bool IntersectsRay(
		const FVector& rayOrigin,
		const FVector& rayDir,
		const FVector& boxCenter,
		FVector& boxHalfSize,
		FVector boxAxes[3],
		float& hitDistance);
    bool IntersectsRayAABB(const FVector& rayOrigin, const FVector& rayDir,
        const FVector& aabbMin, const FVector& aabbMax,
        float& hitDistance)
    {
        float tMin = (aabbMin.x - rayOrigin.x) / rayDir.x;
        float tMax = (aabbMax.x- rayOrigin.x) / rayDir.x;
        if (tMin > tMax) std::swap(tMin, tMax);

        float tyMin = (aabbMin.y - rayOrigin.y) / rayDir.y;
        float tyMax = (aabbMax.y - rayOrigin.y) / rayDir.y;
        if (tyMin > tyMax) std::swap(tyMin, tyMax);

        if ((tMin > tyMax) || (tyMin > tMax))
            return false;

        if (tyMin > tMin) tMin = tyMin;
        if (tyMax < tMax) tMax = tyMax;

        float tzMin = (aabbMin.z - rayOrigin.z) / rayDir.z;
        float tzMax = (aabbMax.z - rayOrigin.z) / rayDir.z;
        if (tzMin > tzMax) std::swap(tzMin, tzMax);

        if ((tMin > tzMax) || (tzMin > tMax))
            return false;

        hitDistance = tMin > 0 ? tMin : tMax;
        return (hitDistance > 0);
    }

    virtual void GenerateRayForPicking(const FVector& pickPosition, const FVector& rayDirection, const FMatrix& viewMatrix);

    //bool IntersectsRayOBB_LocalSpace(const FVector& rayOrigin,  FVector& rayDir,
    //    const FVector& boxCenter, const FVector& boxHalfSize,
    //    const FVector boxAxes[3], float& hitDistance)
    //{
    //    // OBB의 로컬 공간으로 변환 (Ray를 OBB 좌표계로 변환)
    //    FVector localRayOrigin = FVector(
    //        (rayOrigin - boxCenter).Dot(boxAxes[0]),
    //        (rayOrigin - boxCenter).Dot(boxAxes[1]),
    //        (rayOrigin - boxCenter).Dot(boxAxes[2])
    //    );

    //    FVector localRayDir = FVector(
    //        rayDir.Dot(boxAxes[0]),
    //        rayDir.Dot(boxAxes[1]),
    //        rayDir.Dot(boxAxes[2])
    //    );

    //    // 이제 OBB가 (0,0,0) 위치의 AABB가 됨 -> Slab Method 적용 가능
    //    return IntersectsRayAABB(localRayOrigin, localRayDir,
    //        -boxHalfSize, boxHalfSize, hitDistance);
    //}

};