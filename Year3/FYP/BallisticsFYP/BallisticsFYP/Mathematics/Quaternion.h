#pragma once

#include "Vector3.h"

class Quaternion
{
public:
	float w;
	Vector3 vector;

	Quaternion(void);
	Quaternion(const Quaternion& rhs);
	Quaternion(const Vector3& vector, const float& w);
	Quaternion(const float& x, const float& y, const float& z, const float& w);
	~Quaternion(void);

	float Magnitude(void) const;

	Quaternion& operator+=(const Quaternion& quat);
	Quaternion& operator-=(const Quaternion& quat);
	Quaternion& operator*=(const float& scalar);
	Quaternion& operator/=(const float& scalar);

	Quaternion& Conjugate(void) const;
};