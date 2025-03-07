#pragma once
#include <cmath>

struct FVector {
	float x, y, z;
	FVector(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
	FVector operator*(float scalar) const {
		return FVector(x * scalar, y * scalar, z * scalar);
	}
	FVector operator*(const FVector& rhs) const {
		return FVector(x * rhs.x, y * rhs.y, z * rhs.z);
	}
	FVector operator-(const FVector& rhs) const {
		return FVector(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	FVector operator+(const FVector& rhs) const {
		return FVector(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	FVector operator/(float scalar) const {
		if ( scalar == 0 ) return FVector();
		return FVector(x / scalar, y / scalar, z / scalar);
	}
	FVector& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	FVector& operator+=(const FVector& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	FVector& operator-=(const FVector& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	float Dot(const FVector& rhs) {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	FVector Cross(const FVector& rhs) {
		return FVector(
			y*rhs.z - z*rhs.y,
			z*rhs.x - x*rhs.z,
			x*rhs.y - y*rhs.x
		);
	}
	float MagnitudeSquared() const {
		return (x * x + y * y + z * z);
	}
	float Magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}
	FVector Normalized() const {
		float length = Magnitude();

		if ( length != 0 )
			return *this / length;

		return FVector();
	}
};

struct FVector4 {
	float x, y, z, w;
	FVector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) : x(_x), y(_y), z(_z), w(_w) {}
	FVector4 operator*(float scalar) const {
		return FVector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}
	FVector4 operator*(const FVector4& rhs) const {
		return FVector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}
	FVector4 operator-(const FVector4& rhs) const {
		return FVector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}
	FVector4 operator+(const FVector4& rhs) const {
		return FVector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}
	FVector4 operator/(float scalar) const {
		if ( scalar == 0 ) return FVector4();
		return FVector4(x / scalar, y / scalar, z / scalar, w / scalar);
	}
	FVector4& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w += scalar;
		return *this;
	}
	FVector4& operator+=(const FVector4& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}
	FVector4& operator-=(const FVector4& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}
	float Dot(const FVector4& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}
	float MagnitudeSquared() const {
		return (x * x + y * y + z * z + w * w);
	}
	float Magnitude() const {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}
	FVector4 Normalized() const {
		float length = Magnitude();

		if ( length != 0 )
			return *this / length;

		return FVector4();
	}
};