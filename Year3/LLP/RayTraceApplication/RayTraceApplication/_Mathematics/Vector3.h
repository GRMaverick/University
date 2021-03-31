#pragma once

#include <iostream>

class MemoryPool;

class Vector3
{
public:
	float x;
	float y;
	float z;

	static MemoryPool* MemoryPool;

public:
	Vector3(void);
	Vector3(float xyz);
	Vector3(float x, float y, float z);

	void* operator new (size_t size);
	void operator delete(void* pMemory);

	Vector3 operator+(const Vector3 &v) const;
	Vector3 operator-(void) const;
	Vector3 operator-(const Vector3 &v) const;

	Vector3 operator*(const float &f) const;
	Vector3 operator*(const Vector3 &v) const;
	Vector3 Vector3::operator/(const float& scalar) const;

	Vector3& operator+=(const Vector3 &vector);
	Vector3& operator-=(const Vector3& vector);
	Vector3& operator*=(const Vector3 &vector);

	bool operator==(const Vector3& vector) const;
	bool operator!=(const Vector3& vector) const;

	Vector3& Normalise();
	Vector3 Negate(void) const;

	float Length(void) const;
	float LengthSquared(void) const;
	float Dot(const Vector3 &v) const;

	friend std::ostream& operator<<(std::ostream &ostream, const Vector3 &vector)
	{
		ostream << "[" << vector.x << " " << vector.y << " " << vector.z << "]";
		return ostream;
	};
};
