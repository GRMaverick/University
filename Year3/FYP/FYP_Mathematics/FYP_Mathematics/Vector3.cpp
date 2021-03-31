#include "pch.h"
#include "Vector3.h"
#include <algorithm>

Vector3::Vector3(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}
Vector3::Vector3(float xyz)
{
	this->x = xyz;
	this->y = xyz;
	this->z = xyz;
}
Vector3::Vector3(const Vector3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3::~Vector3(void)
{

}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}
Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}
Vector3 Vector3::operator*(const float& scalar) const
{
	return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}

void Vector3::operator+=(const Vector3& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
}
void Vector3::operator-=(const Vector3& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
}

float				Vector3::Dot(const Vector3& rhs) const
{
	return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z);
}
float				Vector3::AngleInDegrees(const Vector3& rhs) const
{
	return acos(this->Dot(rhs) / (this->Magnitude() * rhs.Magnitude())) * (180 / 3.14159265359);
}
float				Vector3::Magnitude(void) const
{
	return floorf(sqrt(this->x * this->x + this->y * this->y + this->z * this->z) * 100000 + 0.5) / 100000;
}
Vector3		Vector3::Negate(void) const
{
	return Vector3(-this->x, -this->y, -this->z);
}
Vector3		Vector3::Normalise(void) const
{
	return Vector3(this->x / Magnitude(), this->y / Magnitude(), this->z / Magnitude());
}

Vector3		Vector3::Cross(const Vector3& rhs) const
{
	return Vector3(	this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z, this->x * rhs.y - this->y * rhs.x);
}