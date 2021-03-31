#include "stdafx.h"
#include "Vector3.h"
#include <algorithm>
namespace Mathematics
{
	namespace Structures
	{
		Vector3::Vector3(void)
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->m_IsNormalised = false;
		}
		Vector3::Vector3(const float& xyz)
		{
			this->x = xyz;
			this->y = xyz;
			this->z = xyz;
			this->m_IsNormalised = false;
		}
		Vector3::Vector3(const Vector3& rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			this->m_IsNormalised = rhs.m_IsNormalised;
		}
		Vector3::Vector3(const float& x, const float& y, const float& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->m_IsNormalised = false;
		}
		Vector3::~Vector3(void)
		{

		}

		bool Vector3::IsNormalised(void) const
		{
			return m_IsNormalised;
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
		Vector3 Vector3::operator/(const float& scalar) const
		{
			return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
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
		void Vector3::operator*=(const Vector3& rhs)
		{
			this->x *= rhs.x;
			this->y *= rhs.y;
			this->z *= rhs.z;
		}
		void Vector3::operator/=(const Vector3& rhs)
		{
			this->x /= rhs.x;
			this->y /= rhs.y;
			this->z /= rhs.z;
		}

		float			Vector3::Dot(const Vector3& rhs) const
		{
			return (float)(this->x * rhs.x + this->y * rhs.y + this->z * rhs.z);
		}
		float			Vector3::AngleInRadians(const Vector3& rhs) const
		{
			return acos(this->Dot(rhs) / (this->Magnitude() * rhs.Magnitude()));
		}
		float			Vector3::AngleInDegrees(const Vector3& rhs) const
		{
			return acos(this->Dot(rhs) / (this->Magnitude() * rhs.Magnitude())) * (180 / 3.14159265359);
		}
		float			Vector3::Magnitude(void) const
		{
			return floorf(sqrt(this->x * this->x + this->y * this->y + this->z * this->z) * 100000 + 0.5) / 100000;
		}

		Vector3		Vector3::Negate(void) const
		{
			return Vector3(-this->x, -this->y, -this->z);
		}
		Vector3		Vector3::Normalise(void)
		{
			this->m_IsNormalised = true;
			return Vector3(this->x / Magnitude(), this->y / Magnitude(), this->z / Magnitude());
		}
		Vector3		Vector3::Cross(const Vector3& rhs) const
		{
			return Vector3(this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z, this->x * rhs.y - this->y * rhs.x);
		}
	}
}