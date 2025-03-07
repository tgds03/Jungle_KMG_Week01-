#include "stdafx.h"

const FMatrix FMatrix::Identity = FMatrix({
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f,
});

FMatrix::FMatrix(float m[4][4]) {
	memcpy(this->m, m, sizeof(float) * 4 * 4);
}

FMatrix::FMatrix(FVector4 r[4]) {
	this->m[0][0] = r[0].x; this->m[0][1] = r[0].y; this->m[0][2] = r[0].z; this->m[0][3] = r[0].w;
	this->m[1][0] = r[1].x; this->m[1][1] = r[1].y; this->m[1][2] = r[1].z; this->m[1][3] = r[1].w;
	this->m[2][0] = r[2].x; this->m[2][1] = r[2].y; this->m[2][2] = r[2].z; this->m[2][3] = r[2].w;
	this->m[3][0] = r[3].x; this->m[3][1] = r[3].y; this->m[3][2] = r[3].z; this->m[3][3] = r[3].w;

}

FMatrix::FMatrix(const std::initializer_list<float>& m) {
	if ( m.size() != 16 ) 
		return;
	int i = 0;
	for (auto f: m) {
		this->m[i/4][i%4] = f;
		++i;
	}
}

FMatrix FMatrix::operator+(const FMatrix& rhs) const {
	float m[4][4] = {
		{this->m[0][0] + rhs.m[0][0], this->m[0][1] + rhs.m[0][1], this->m[0][2] + rhs.m[0][2], this->m[0][3] + rhs.m[0][3]},
		{this->m[1][0] + rhs.m[1][0], this->m[1][1] + rhs.m[1][1], this->m[1][2] + rhs.m[1][2], this->m[1][3] + rhs.m[1][3]},
		{this->m[2][0] + rhs.m[2][0], this->m[2][1] + rhs.m[2][1], this->m[2][2] + rhs.m[2][2], this->m[2][3] + rhs.m[2][3]},
		{this->m[3][0] + rhs.m[3][0], this->m[3][1] + rhs.m[3][1], this->m[3][2] + rhs.m[3][2], this->m[3][3] + rhs.m[3][3]},
	};
	return FMatrix(m);
}

FMatrix FMatrix::operator-(const FMatrix& rhs) const {
	float m[4][4] = {
		{this->m[0][0] - rhs.m[0][0], this->m[0][1] - rhs.m[0][1], this->m[0][2] - rhs.m[0][2], this->m[0][3] - rhs.m[0][3]},
		{this->m[1][0] - rhs.m[1][0], this->m[1][1] - rhs.m[1][1], this->m[1][2] - rhs.m[1][2], this->m[1][3] - rhs.m[1][3]},
		{this->m[2][0] - rhs.m[2][0], this->m[2][1] - rhs.m[2][1], this->m[2][2] - rhs.m[2][2], this->m[2][3] - rhs.m[2][3]},
		{this->m[3][0] - rhs.m[3][0], this->m[3][1] - rhs.m[3][1], this->m[3][2] - rhs.m[3][2], this->m[3][3] - rhs.m[3][3]},
	};
	return FMatrix(m);
}

FMatrix FMatrix::operator*(const float& rhs) const {
	float m[4][4] = {
		{this->m[0][0] * rhs, this->m[0][1] * rhs, this->m[0][2] * rhs, this->m[0][3] * rhs},
		{this->m[1][0] * rhs, this->m[1][1] * rhs, this->m[1][2] * rhs, this->m[1][3] * rhs},
		{this->m[2][0] * rhs, this->m[2][1] * rhs, this->m[2][2] * rhs, this->m[2][3] * rhs},
		{this->m[3][0] * rhs, this->m[3][1] * rhs, this->m[3][2] * rhs, this->m[3][3] * rhs},
	};
	return FMatrix(m);
}

FMatrix FMatrix::operator*(const FMatrix& rhs) const {
	return FMatrix({
		r1().Dot(rhs.c1()), r1().Dot(rhs.c2()), r1().Dot(rhs.c3()), r1().Dot(rhs.c4()),
		r2().Dot(rhs.c1()), r2().Dot(rhs.c2()), r2().Dot(rhs.c3()), r2().Dot(rhs.c4()),
		r3().Dot(rhs.c1()), r3().Dot(rhs.c2()), r3().Dot(rhs.c3()), r3().Dot(rhs.c4()),
		r4().Dot(rhs.c1()), r4().Dot(rhs.c2()), r4().Dot(rhs.c3()), r4().Dot(rhs.c4()),
	});
}

FVector4 FMatrix::operator*(const FVector4& rhs) const {
	return FVector4(rhs.Dot(c1()), rhs.Dot(c2()), rhs.Dot(c3()), rhs.Dot(c4()));
}

FVector4 FMatrix::r1() const { return FVector4(m[0][0], m[0][1], m[0][2], m[0][3]); }

FVector4 FMatrix::r2() const { return FVector4(m[1][0], m[1][1], m[1][2], m[1][3]); }

FVector4 FMatrix::r3() const { return FVector4(m[2][0], m[2][1], m[2][2], m[2][3]); }

FVector4 FMatrix::r4() const { return FVector4(m[3][0], m[3][1], m[3][2], m[3][3]); }

FVector4 FMatrix::c1() const { return FVector4(m[0][0], m[1][0], m[2][0], m[3][0]); }

FVector4 FMatrix::c2() const { return FVector4(m[0][1], m[1][1], m[2][1], m[3][1]); }

FVector4 FMatrix::c3() const { return FVector4(m[0][2], m[1][2], m[2][2], m[3][2]); }

FVector4 FMatrix::c4() const { return FVector4(m[0][3], m[1][3], m[2][3], m[3][3]); }

FMatrix FMatrix::Scale(float sx, float sy, float sz) {
	return FMatrix({
		sx, 0.f, 0.f, 0.f,
		0.f, sy, 0.f, 0.f,
		0.f, 0.f, sz, 0.f,
		0.f, 0.f, 0.f, 1.f
	});
}

FMatrix FMatrix::RotateX(float rx) {
	return FMatrix({
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, cos(rx), -sin(rx), 0.f,
		0.f, sin(rx), cos(rx), 1.f
	});
}

FMatrix FMatrix::RotateY(float ry) {
	return FMatrix({
		cos(ry), 0.f, sin(ry), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sin(ry), 0.f, cos(ry), 0.f,
		0.f, 0.f, 0.f, 1.f,
	});
}

FMatrix FMatrix::RotateZ(float rz) {
	return FMatrix({
		cos(rz), -sin(rz), 0.f, 0.f,
		sin(rz), cos(rz), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f,
	});
}

FMatrix FMatrix::Translate(float tx, float ty, float tz) {
	return FMatrix({
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		tx, ty, tz, 1.f
	});
}
