#pragma once

#include "Vector3.h"

namespace Mathematics
{
	namespace Structures
	{
		class Matrix3x3
		{
		public:
			float row1[3];
			float row2[3];
			float row3[3];

			Matrix3x3(void);
			Matrix3x3(float e11, float e12, float e13, float e21, float e22, float e23, float e31, float e32, float e33);
			Matrix3x3(const Matrix3x3& matrix);
			~Matrix3x3(void);

			Matrix3x3 operator+(Matrix3x3& matrix);
			Matrix3x3 operator-(Matrix3x3& matrix);
			Matrix3x3 operator*(Matrix3x3& matrix);

			Matrix3x3 operator*(float& scalar);
			Matrix3x3 operator/(float& scalar);

			Matrix3x3& operator+=(Matrix3x3& matrix);
			Matrix3x3& operator-=(Matrix3x3& matrix);
			Matrix3x3& operator*=(float& scalar);
			Matrix3x3& operator/=(float& scalar);

			float Determinant(void);
			Matrix3x3 Transpose(void);
			Matrix3x3 Inverse(void);

			static Vector3& VectorMultiply(const Vector3& vector, const Matrix3x3& matrix);
		};
	}
}