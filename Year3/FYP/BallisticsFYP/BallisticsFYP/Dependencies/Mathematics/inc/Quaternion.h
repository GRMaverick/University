#pragma once

#include "Vector3.h"

namespace Mathematics
{
	namespace Structures
	{
		class Quaternion
		{
		public:
			float w;
			Vector3 vector;

			// Default
			Quaternion(void);
			// From Euler
			Quaternion(const Vector3& rhs);
			// Copy
			Quaternion(const Quaternion& rhs);
			// Vector-Scalar
			Quaternion(const Vector3& vector, const float& w);
			// Explicit Component-Wise
			Quaternion(const float& x, const float& y, const float& z, const float& w);
			~Quaternion(void);

			float Magnitude(void) const;

			Quaternion& operator+=(const Quaternion& quat);
			Quaternion& operator-=(const Quaternion& quat);
			Quaternion& operator*(const Quaternion& quat);
			Quaternion& operator*=(const Quaternion& scalar);

			Quaternion& Conjugate(void) const;
			Quaternion& Normalise(void) const;
			Quaternion& RotateByVector(const Vector3& vector);

			void				 FromEuler(const Vector3& vector);
			Vector3&		 ToEuler(void) const;
		};
	}
}