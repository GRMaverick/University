
#include "pch.h"
#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion(void)
{
	this->w = 0.0f;
	this->vector = Vector3(0.0f);
}
Quaternion::Quaternion(const Quaternion& rhs)
{
	this->w = rhs.w;
	this->vector = rhs.vector;
}
Quaternion::Quaternion(const Vector3& vector, const float& w)
{
	this->w = w;
	this->vector = vector;
}
Quaternion::Quaternion(const float& x, const float& y, const float& z, const float& w)
{
	this->w = w;
	this->vector = Vector3(x, y, z);
}
Quaternion::~Quaternion(void)
{
}

float Quaternion::Magnitude(void) const
{
	return (float)sqrt((vector.x*vector.x) + (vector.y*vector.y) + (vector.z*vector.z) + (w*w));
}

Quaternion& Quaternion::operator+=(const Quaternion& quat)
{
	vector += quat.vector;
	w += quat.w;
	return *this;
}
Quaternion& Quaternion::operator-=(const Quaternion& quat)
{
	vector -= quat.vector;
	w -= quat.w;
	return *this;
}
Quaternion& Quaternion::operator*=(const float& scalar)
{
	vector *= scalar;
	w *= scalar;
	return *this;
}
Quaternion& Quaternion::operator/=(const float& scalar)
{
	vector /= scalar;
	w /= scalar;
	return *this;
}

Quaternion& Quaternion::Conjugate(void) const
{
	return Quaternion(-vector.x, -vector.y, -vector.z, w);
}
