#include "Quaternion.h"
//#include "Matrix3x3.h"
#include "Vector3.h"

DPHYSX_DLL Quaternion::Quaternion(void) { 
	this->x = 0.0f; 
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}
DPHYSX_DLL Quaternion::Quaternion(float w, float x, float y, float z) { 
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w; 
}
DPHYSX_DLL Quaternion::~Quaternion(void) 
{ 
}

DPHYSX_DLL Quaternion Quaternion::operator+(Quaternion quat) 
{ 
	return Quaternion(w + quat.w, x + quat.x, y + quat.y, z + quat.z); 
}
DPHYSX_DLL Quaternion Quaternion::operator-(Quaternion quat) 
{ 
	return Quaternion(w - quat.w, x - quat.x, y - quat.y, z - quat.z); 
}
DPHYSX_DLL Quaternion Quaternion::operator*(float scalar) 
{ 
	return Quaternion(w * scalar, x * scalar, y *scalar, z * scalar); 
}

DPHYSX_DLL Quaternion Quaternion::operator*(Quaternion quat)
{
	return	Quaternion(w*quat.w - x*quat.x - y*quat.y - z*quat.z,
		w*quat.x + x*quat.w + y*quat.z - z*quat.y,
		w*quat.y + y*quat.w + z*quat.x - x*quat.z,
		w*quat.z + z*quat.w + x*quat.y - y*quat.x);
}
DPHYSX_DLL Quaternion Quaternion::operator*(Vector3 vector)
{
	return	Quaternion(-(x*vector.x + y*vector.y + z*vector.z),
		w*vector.x + y*vector.z - z*vector.y,
		w*vector.y + z*vector.x - x*vector.z,
		w*vector.z + x*vector.y - y*vector.x);
}

DPHYSX_DLL Quaternion Quaternion::operator/(float scalar)
{ 
	return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar); 
}
DPHYSX_DLL Quaternion Quaternion::operator~(void) 
{ 
	return Quaternion(w, -x, -y, -z); 
}

DPHYSX_DLL Quaternion Quaternion::operator+=(Quaternion quat) 
{ 
	return Quaternion(w += quat.w, x += quat.x, y += quat.y, z += quat.z); 
}
DPHYSX_DLL Quaternion Quaternion::operator-=(Quaternion quat) 
{ 
	return Quaternion(w -= quat.w, x -= quat.x, y -= quat.y, z -= quat.z); 
}
DPHYSX_DLL Quaternion Quaternion::operator*=(Quaternion quat) 
{ 
	return Quaternion(w *= quat.w, x *= quat.x, y *= quat.y, z *= quat.z); 
}
DPHYSX_DLL Quaternion Quaternion::operator/=(Quaternion quat) 
{ 
	return Quaternion(w /= quat.w, x /= quat.x, y /= quat.y, z /= quat.z); 
}

DPHYSX_DLL float Quaternion::GetQuaternionAngle(void) const 
{ 
	return (float)(2 * acos(w)); 
}
DPHYSX_DLL float Quaternion::GetScalar(void) const 
{ 
	return w; 
}
DPHYSX_DLL Vector3 Quaternion::GetVector(void) const 
{ 
	return Vector3(x, y, z); 
}

DPHYSX_DLL Vector3 Quaternion::GetQuaternionAxis(void)
{
	if (Vector3(x, y, z).Magnitude() <= FPOINT_TOLERANCE)
		return Vector3();
	else
		return Vector3(x, y, z) /= Vector3(x, y, z).Magnitude();
}
DPHYSX_DLL Vector3 Quaternion::QuaternionVectorRotate(Vector3 vector)
{
	Quaternion quat;

	quat = *this * vector * (~*this);

	return quat.GetVector();
}
DPHYSX_DLL Vector3 Quaternion::MakeEulerFromQuaternion(void)
{
	Vector3 vector;
	float tmp;
	float wW, xX, yY, zZ;
	float r11, r21, r31, r32, r33, r12, r13;

	wW = w*w;
	xX = x*x;
	yY = y*y;
	zZ = z*z;

	r11 = wW + xX - yY - zZ;
	r21 = 2 * (x * y + w * z);
	r31 = 2 * (x * z - w * y);
	r32 = 2 * (y * z + w * x);
	r33 = wW - xX - yY + zZ;

	tmp = fabs(r31);

	if (tmp > 0.999999)
	{
		r12 = 2 * (x * y - w * z);
		r13 = 2 * (x * z + w * y);

		vector.x = RADIANS_TO_DEGREES(0.0f);
		vector.y = RADIANS_TO_DEGREES((float)(-(PI / 2) * r31 / tmp));
		vector.z = RADIANS_TO_DEGREES((float)atan2(-r12, -r13*r13));
		return vector;
	}

	vector.x = RADIANS_TO_DEGREES((float)atan2(r32, r33));
	vector.y = RADIANS_TO_DEGREES((float)asin(-r31));
	vector.z = RADIANS_TO_DEGREES((float)atan2(r21, r11));

	return vector;
}

DPHYSX_DLL Quaternion Quaternion::MakeQuaternionFromEuler(float x, float y, float z)
{
	Quaternion quat;

	float roll = DEGREES_TO_RADIANS(x);
	float pitch = DEGREES_TO_RADIANS(y);
	float yaw = DEGREES_TO_RADIANS(z);

	float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;
	float cYawcPitch, sYawsPitch, cYawSPitch, sYawCPitch;

	cYaw = cos(0.5f * yaw);
	cPitch = cos(0.5f * pitch);
	cRoll = cos(0.5f * roll);
	sYaw = sin(0.5f * yaw);
	sPitch = sin(0.5f * pitch);
	sRoll = sin(0.5f * roll);

	cYawcPitch = cYaw*cPitch;
	sYawsPitch = sYaw*sPitch;
	cYawSPitch = cYaw*sPitch;
	sYawCPitch = sYaw*cPitch;

	quat.w = (float)(cYawcPitch * cRoll + sYawsPitch * sRoll);
	quat.x = (float)(cYawcPitch * sRoll - sYawsPitch * cRoll);
	quat.y = (float)(cYawSPitch * cRoll + sYawCPitch * sRoll);
	quat.z = (float)(sYawCPitch * cRoll - cYawSPitch * sRoll);

	return quat;
}
DPHYSX_DLL Quaternion Quaternion::QuaternionRotate(Quaternion quat)
{
	return (*this * quat)*(~*this);

}

//DPHYSX_DLL Matrix3x3 Quaternion::MakeMatrixFromQuaternion(Quaternion quat)
//{
//
//}

DPHYSX_DLL float Quaternion::Magnitude(void) 
{ 
	return (float)sqrt(w*w + x*x + y*y + z*z); 
}