#pragma once
#ifndef __DPHYSX_QUATERNION__
#define __DPHYSX_QUATERNION__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

#include <math.h>
#include "Commons.h"

class Vector3;
//class Matrix3x3;

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	DPHYSX_DLL Quaternion(void);
	DPHYSX_DLL Quaternion(float w, float x, float y, float z);
	DPHYSX_DLL ~Quaternion(void);

	DPHYSX_DLL inline Quaternion operator+(Quaternion quat); 
	DPHYSX_DLL inline Quaternion operator-(Quaternion quat); 
	DPHYSX_DLL inline Quaternion operator*(float scalar);
	DPHYSX_DLL inline Quaternion operator*(Quaternion quat);
	DPHYSX_DLL inline Quaternion operator*(Vector3 vector);
	DPHYSX_DLL inline Quaternion operator/(float scalar);
	DPHYSX_DLL inline Quaternion operator~(void);

	DPHYSX_DLL inline Quaternion operator+=(Quaternion quat);
	DPHYSX_DLL inline Quaternion operator-=(Quaternion quat);
	DPHYSX_DLL inline Quaternion operator*=(Quaternion quat);
	DPHYSX_DLL inline Quaternion operator/=(Quaternion quat);


	DPHYSX_DLL inline float GetQuaternionAngle(void) const;
	DPHYSX_DLL inline float GetScalar(void) const;
	DPHYSX_DLL inline Vector3 GetVector(void) const;
	DPHYSX_DLL Vector3 GetQuaternionAxis(void);
	DPHYSX_DLL Vector3 QuaternionVectorRotate(Vector3 vector);
	DPHYSX_DLL Vector3 MakeEulerFromQuaternion(void);

	DPHYSX_DLL Quaternion MakeQuaternionFromEuler(float x, float y, float z);
	DPHYSX_DLL Quaternion QuaternionRotate(Quaternion quat);

	//DPHYSX_DLL Matrix3x3 MakeMatrixFromQuaternion(Quaternion quat);

	DPHYSX_DLL inline float Magnitude(void);
}; 
#endif