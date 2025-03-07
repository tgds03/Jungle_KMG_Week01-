#pragma once
#include <cmath>
#include <initializer_list>
#include "FVector.h"

struct FMatrix {
public:
	float m[4][4];
	FMatrix(float[4][4]);
	FMatrix(FVector4 r[4]);
	FMatrix(const std::initializer_list<float>& m);

	FMatrix operator+(const FMatrix& rhs) const;
	FMatrix operator-(const FMatrix& rhs) const;
	FMatrix operator*(const float& rhs) const;
	FMatrix operator*(const FMatrix& rhs) const;
	FVector4 operator[](int row){
		return FVector4(m[row][0], m[row][1], m[row][2], m[row][3]);
	}
	
//FVector4 operator*(const FVector4& rhs) const;

	FVector4 r1() const;
	FVector4 r2() const;
	FVector4 r3() const;
	FVector4 r4() const;

	FVector4 c1() const;
	FVector4 c2() const;
	FVector4 c3() const;
	FVector4 c4() const;

	FMatrix Transpose() const;
	friend FVector4 operator*(const FVector4& lhs, const FMatrix& rhs);

public:
	static const FMatrix Identity;
	static FMatrix Scale(float sx, float sy, float sz);
	static FMatrix RotateX(float rx);
	static FMatrix RotateY(float ry);
	static FMatrix RotateZ(float rz);
	static FMatrix Translate(float tx, float ty, float tz);
};
