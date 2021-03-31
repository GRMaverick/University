#pragma once

#include "Line.h"
#include "Vector3.h"

namespace Mathematics
{
	namespace Structures
	{
		class Plane
		{
		public:
			Plane(void);
			Plane(const Plane& rhs);
			Plane(const Vector3& point, const Vector3& normal, const Vector3& extents = Vector3(-1.0f, -1.0f, -1.0f));

			void SetPoint(const Vector3& point);
			void SetNormal(const Vector3& normal);
			void SetExtents(const Vector3& extents);

			Vector3 GetPoint(void) const;
			Vector3 GetNormal(void) const;
			Vector3 GetExtents(void) const;

		private:
			Vector3 m_Point;
			Vector3 m_Normal;
			Vector3 m_Extents;
		};
	}
}