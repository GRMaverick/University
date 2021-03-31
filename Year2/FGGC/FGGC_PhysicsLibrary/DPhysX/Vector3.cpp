#include "Vector3.h"
#include "Quaternion.h"

#define DPHYSX_DLL_EXPORT

DPHYSX_DLL Vector3::Vector3(void)
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
DPHYSX_DLL Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
DPHYSX_DLL Vector3::~Vector3(void)
{

}

DPHYSX_DLL bool Vector3::operator==(Vector3& vector)
{
	return (this->x == vector.x && this->y == vector.y && this->z == vector.z);
}
DPHYSX_DLL bool Vector3::operator!=(Vector3& vector)
{
	return !(this->operator!=(vector));
}

DPHYSX_DLL Vector3 Vector3::operator=(Vector3& vector)
{
	return Vector3(this->x = vector.x, this->y = vector.y, this->z = vector.z);
}
DPHYSX_DLL Vector3 Vector3::operator+(Vector3& vector)
{
	return Vector3(this->x + vector.x, this->y + vector.y, this->z + vector.z);
}
DPHYSX_DLL Vector3 Vector3::operator-(Vector3& vector)
{
	return Vector3(this->x - vector.x, this->y - vector.y, this->z - vector.z);
}
DPHYSX_DLL Vector3 Vector3::operator+=(Vector3& vector)
{
	return Vector3(this->x += vector.x, this->y += vector.y, this->z += vector.z);
}
DPHYSX_DLL Vector3 Vector3::operator-=(Vector3& vector)
{
	return Vector3(this->x -= vector.x, this->y -= vector.y, this->z -= vector.z);
}
DPHYSX_DLL Vector3 Vector3::operator^(Vector3& vector)
{
	return Vector3(this->y*vector.z - this->z*vector.y, -this->x*vector.z + this->z*vector.x, this->x*vector.y - this->y*vector.x);
}

DPHYSX_DLL Vector3 Vector3::operator*(float scalar)
{
	return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}
DPHYSX_DLL Vector3 Vector3::operator/(float scalar)
{
	return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
}

DPHYSX_DLL Vector3 Vector3::operator*=(float scalar)
{
	return Vector3(this->x *= scalar, this->y *= scalar, this->z *= scalar);
}
DPHYSX_DLL Vector3 Vector3::operator/=(float scalar)
{
	return Vector3(this->x /= scalar, this->y /= scalar, this->z /= scalar);
}

DPHYSX_DLL Quaternion Vector3::operator*(Quaternion& q)
{
	return Quaternion(-(q.x*x + q.y*y + q.z*z), 
										q.w*x + q.z*y - q.y*z,
										 q.w*y + q.x*z - q.z*x,
										q.w*z + q.y*x - q.x*y);
}

DPHYSX_DLL Vector3 Vector3::operator*(Matrix3x3 matrix)
{
	return Vector3(matrix.m11*x + matrix.m12*y + matrix.m13*z,
		matrix.m21*x + matrix.m22*y + matrix.m23*z,
		matrix.m31*x + matrix.m32*y + matrix.m33*z);
}

DPHYSX_DLL float Vector3::operator*(Vector3& v)
{
	return (x * v.x) + (y*v.y) + (z * v.z);
}

DPHYSX_DLL void Vector3::Negate(void)
{ 
	this->x = -this->x; this->y = -this->y; this->z = -this->z; 
}
DPHYSX_DLL void Vector3::Normalise(void)
{ 
	*this = *this /= this->Magnitude(); 
}
DPHYSX_DLL float Vector3::Magnitude(void)
{ 
	return (float)sqrt(this->x*this->x + this->y*this->y + this->z*this->z); 
}
