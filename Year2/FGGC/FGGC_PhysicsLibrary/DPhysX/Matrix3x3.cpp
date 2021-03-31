#include "Matrix3x3.h"

#define DPHYSX_DLL_EXPORT

DPHYSX_DLL Matrix3x3::Matrix3x3(void)
{
	m11 = 0.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 0.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 0.0f;
}
DPHYSX_DLL Matrix3x3::Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m31 = m31; this->m32 = m32; this->m33 = m33;
}

DPHYSX_DLL Matrix3x3& Matrix3x3::operator+=(Matrix3x3 m)
{
	return Matrix3x3(this->m11 += m.m11, this->m12 += m.m12, this->m13 += m.m13,
		this->m21 += m.m21, this->m22 += m.m22, this->m23 += m.m23,
		this->m31 += m.m31, this->m32 += m.m32, this->m33 += m.m33);
}
DPHYSX_DLL Matrix3x3& Matrix3x3::operator-=(Matrix3x3 m)
{
	return Matrix3x3(this->m11 -= m.m11, this->m12 -= m.m12, this->m13 -= m.m13,
		this->m21 -= m.m21, this->m22 -= m.m22, this->m23 -= m.m23,
		this->m31 -= m.m31, this->m32 -= m.m32, this->m33 -= m.m33);
}
DPHYSX_DLL Matrix3x3& Matrix3x3::operator*=(float scalar)
{
	return Matrix3x3(this->m11 *= scalar, this->m12 *= scalar, this->m13 *= scalar,
		this->m21 *= scalar, this->m22 *= scalar, this->m23 *= scalar,
		this->m31 *= scalar, this->m32 *= scalar, this->m33 *= scalar);
}
DPHYSX_DLL Matrix3x3& Matrix3x3::operator/=(float scalar)
{
	return Matrix3x3(this->m11 /= scalar, this->m12 /= scalar, this->m13 /= scalar,
		this->m21 /= scalar, this->m22 /= scalar, this->m23 /= scalar,
		this->m31 /= scalar, this->m32 /= scalar, this->m33 /= scalar);
}

DPHYSX_DLL float Matrix3x3::Det(void)
{
	return	m11*m22*m33 -
		m11*m32*m23 +
		m21*m32*m13 -
		m21*m12*m33 +
		m31*m12*m23 -
		m31*m22*m13;
}

DPHYSX_DLL Matrix3x3 Matrix3x3::Inverse(void)
{
	float	d = Det();

	if (d == 0) d = 1;

	return	Matrix3x3((m22*m33 - m23*m32) / d,
		-(m12*m33 - m13*m32) / d,
		(m12*m23 - m13*m22) / d,
		-(m21*m33 - m23*m31) / d,
		(m11*m33 - m13*m31) / d,
		-(m11*m23 - m13*m21) / d,
		(m21*m32 - m22*m31) / d,
		-(m11*m32 - m12*m31) / d,
		(m11*m22 - m12*m21) / d);
}