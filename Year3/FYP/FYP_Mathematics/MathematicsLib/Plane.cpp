#include "stdafx.h"
#include "Plane.h"

namespace Mathematics
{
	namespace Structures
	{
		Plane::Plane(void)
		{
			this->m_Point = Vector3(0.0f);
			this->m_Normal = Vector3(0.0f);
			this->m_Extents = Vector3(0.0f);
		}
		Plane::Plane(const Plane& rhs)
		{
			this->m_Point = rhs.m_Point;
			this->m_Normal = rhs.m_Normal;
			this->m_Extents = rhs.m_Extents;
		}
		Plane::Plane(const Vector3& point, const Vector3& normal, const Vector3& extents)
		{
			this->m_Point = point;
			this->m_Normal = normal;
			this->m_Extents = extents;
		}

		void Plane::SetPoint(const Vector3& point)
		{
			m_Point = point;
		}
		void Plane::SetNormal(const Vector3& normal)
		{
			m_Normal = normal;
		}
		void Plane::SetExtents(const Vector3& extents)
		{
			m_Extents = extents;
		}

		Vector3 Plane::GetPoint(void) const
		{
			return m_Point;
		}
		Vector3 Plane::GetNormal(void) const
		{
			return m_Normal;
		}
		Vector3 Plane::GetExtents(void) const
		{
			return m_Extents;
		}
	}
}