#include "stdafx.h"
#include "Line.h"

namespace Mathematics
{
	namespace Structures
	{
		Line::Line(void)
		{
			m_Point = Vector3();
			m_Direction = Vector3();
		}
		Line::Line(const Line& rhs)
		{
			m_Point = rhs.m_Point;
			m_Direction = rhs.m_Direction;
		}
		Line::Line(const Vector3& point, const Vector3& direction)
		{
			m_Point = point;
			m_Direction = direction;
		}

		void Line::SetPoint(const Vector3& point)
		{
			m_Point = point;
		}
		void Line::SetDirection(const Vector3& direction)
		{
			m_Direction = direction;
		}

		Vector3 Line::GetPoint(void) const
		{
			return m_Point;
		}
		Vector3 Line::GetDirection(void) const
		{
			return m_Direction;
		}
		Vector3 Line::GetPointOnLine(const float& scalar) const
		{
			return m_Point + (m_Direction * scalar);
		}
	}
}