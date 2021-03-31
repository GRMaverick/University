#ifndef __DPHYSX_VECTOR_3__
#define __DPHYSX_VECTOR_3__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

#include <math.h>
#include "Matrix3x3.h"

class Matrix3x3;
class Quaternion;

class Vector3
{
public:
	float x;
	float y;
	float z;

	DPHYSX_DLL Vector3(void);
	DPHYSX_DLL Vector3(float x, float y, float z);
	DPHYSX_DLL ~Vector3(void);

	DPHYSX_DLL virtual Vector3 operator=(Vector3& vector);

	DPHYSX_DLL bool operator==(Vector3& vector);
	DPHYSX_DLL bool operator!=(Vector3& vector);
		
	DPHYSX_DLL Vector3 operator+(Vector3& vector);
	DPHYSX_DLL Vector3 operator-(Vector3& vector);
	DPHYSX_DLL Vector3 operator*(float scalar);
	DPHYSX_DLL Vector3 operator/(float scalar);

	DPHYSX_DLL Vector3 operator+=(Vector3& vector);
	DPHYSX_DLL Vector3 operator-=(Vector3& vector);
	DPHYSX_DLL Vector3 operator*=(float scalar);
	DPHYSX_DLL Vector3 operator/=(float scalar);

	DPHYSX_DLL Quaternion operator*(Quaternion& quaternion);
	
	DPHYSX_DLL Vector3 operator^(Vector3& vector);

	DPHYSX_DLL Vector3 operator*(Matrix3x3 matrix);

	// When writing the class to return Vector3 using Matrix3x3, 
	// Pass through IMatrix3x3
	// Opposite for return Matrix3x3 using IVector3 in function

	DPHYSX_DLL float operator*(Vector3& vector);

	DPHYSX_DLL void Negate(void);
	DPHYSX_DLL void Normalise(void);
	DPHYSX_DLL float Magnitude(void);

	DPHYSX_DLL void Rotate(Quaternion& q);
};

#endif