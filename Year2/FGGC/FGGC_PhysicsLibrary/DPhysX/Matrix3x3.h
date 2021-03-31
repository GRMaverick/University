#ifndef __DPHYSX_MATRIX_3x3__
#define __DPHYSX_MATRIX_3x3__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

class Vector3;

class Matrix3x3
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	DPHYSX_DLL Matrix3x3(void);
	DPHYSX_DLL Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);
	DPHYSX_DLL ~Matrix3x3(void) { }

	DPHYSX_DLL Matrix3x3& operator+=(Matrix3x3 m);
	DPHYSX_DLL Matrix3x3& operator-=(Matrix3x3 m);
	DPHYSX_DLL Matrix3x3& operator*=(float scalar);
	DPHYSX_DLL Matrix3x3& operator/=(float scalar);

	DPHYSX_DLL float Det(void);

	DPHYSX_DLL Matrix3x3 Inverse(void);
	DPHYSX_DLL inline Matrix3x3 Transpose(void) { return Matrix3x3(m11, m21, m31, m12, m22, m32, m13, m23, m33); }
};

#endif