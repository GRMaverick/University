#include "stdafx.h"
#include "Quaternion.h"
#include <math.h>
namespace Mathematics
{
	namespace Structures
	{
		Quaternion::Quaternion(void)
		{
			this->w = 1.0f;
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
		Quaternion& Quaternion::operator*(const Quaternion& multiplier)
		{
			Quaternion q = Quaternion();

			q.w = this->w				*	multiplier.w -
				this->vector.x	*	multiplier.vector.x -
				this->vector.y	*	multiplier.vector.y -
				this->vector.z	*	multiplier.vector.z;

			q.vector.x = this->w				*	multiplier.vector.x +
				this->vector.x	*	multiplier.w +
				this->vector.y	*	multiplier.vector.z -
				this->vector.z	*	multiplier.vector.y;

			q.vector.y = this->w				*	multiplier.vector.y +
				this->vector.y	*	multiplier.w +
				this->vector.z	*	multiplier.vector.x -
				this->vector.x	*	multiplier.vector.z;

			q.vector.z = this->w				*	multiplier.vector.z +
				this->vector.z	*	multiplier.w +
				this->vector.x	*	multiplier.vector.y -
				this->vector.y	*	multiplier.vector.x;
			return q;
		}
		Quaternion& Quaternion::operator*=(const Quaternion& multiplier)
		{
			Quaternion q = *this;

			this->w = q.w				*	multiplier.w -
				q.vector.x		*	multiplier.vector.x -
				q.vector.y		*	multiplier.vector.y -
				q.vector.z		*	multiplier.vector.z;

			this->vector.x = q.w				*	multiplier.vector.x +
				q.vector.x		*	multiplier.w +
				q.vector.y		*	multiplier.vector.z -
				q.vector.z		*	multiplier.vector.y;

			this->vector.y = q.w				*	multiplier.vector.y +
				q.vector.y		*	multiplier.w +
				q.vector.z		*	multiplier.vector.x -
				q.vector.x		*	multiplier.vector.z;

			this->vector.z = q.w				*	multiplier.vector.z +
				q.vector.z		*	multiplier.w +
				q.vector.x		*	multiplier.vector.y -
				q.vector.y		*	multiplier.vector.x;
			return *this;
		}

		Quaternion& Quaternion::Conjugate(void) const
		{
			return Quaternion(-vector.x, -vector.y, -vector.z, w);
		}
		Quaternion& Quaternion::Normalise(void) const
		{
			Quaternion quat;
			float magnitude = (this->vector.x * this->vector.x) + (this->vector.y * this->vector.y) + (this->vector.z * this->vector.z) + (this->w * this->w);

			if (magnitude < 0.0f)
			{
				quat.w = 1.0f;
			}

			magnitude = 1.0f / sqrt(magnitude);
			quat.w *= magnitude;
			quat.vector = quat.vector * magnitude;

			return quat;
		}

		Quaternion& Quaternion::RotateByVector(const Vector3& vector)
		{
			Quaternion q(vector.x, vector.y, vector.z, 0.0f);
			(*this) *= q;

			return *this;
		}
		void				Quaternion::FromEuler(const Vector3& vector)
		{
			float xRadians = vector.x * (3.14159 / 180);
			float yRadians = vector.y * (3.14159 / 180);
			float zRadians = vector.z * (3.14159 / 180);

			Quaternion xQuat = Quaternion((float)sin(xRadians / 2), 0.0f, 0.0f, (float)cos(xRadians / 2));
			Quaternion yQuat = Quaternion(0.0f, (float)sin(yRadians / 2), 0.0f, (float)cos(yRadians / 2));
			Quaternion zQuat = Quaternion(0.0f, 0.0f, (float)sin(zRadians / 2), (float)cos(zRadians / 2));

			Quaternion finalQ = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

			finalQ *= xQuat;
			finalQ *= yQuat;
			finalQ *= zQuat;

			*this = finalQ;
		}
		Vector3&		Quaternion::ToEuler(void) const
		{
			Vector3 vector = Vector3();

			float xSq = this->vector.x * this->vector.x;
			float ySq = this->vector.y * this->vector.y;
			float zSq = this->vector.z * this->vector.z;

			float sinRoll = 2 * (this->w * this->vector.x + this->vector.y * this->vector.z);
			float cosRoll = 1 - 2 * (xSq + ySq);

			float sinPitch = 2 * (this->w * this->vector.y - this->vector.z * this->vector.x);

			float sinYaw = 2 * (this->w * this->vector.z + this->vector.x * this->vector.y);
			float cosYaw = 1 - 2 * (ySq + zSq);

			vector.x = atan2(sinRoll, cosRoll);
			vector.y = (fabs(sinPitch) >= 1) ? copysign(3.14159, sinPitch) : asin(sinPitch);
			vector.z = atan2(sinYaw, cosYaw);

			vector.x = vector.x * (180 / 3.14159);
			vector.y = vector.y * (180 / 3.14159);
			vector.z = vector.z * (180 / 3.14159);

			return vector;
		}
	}
}