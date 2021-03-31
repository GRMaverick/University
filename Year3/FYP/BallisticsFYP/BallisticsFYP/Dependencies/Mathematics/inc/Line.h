#pragma once

#include "Vector3.h"

namespace Mathematics
{
	namespace Structures
	{
		class Line
		{
		public:
			Line(void);
			Line(const Line& rhs);
			Line(const Vector3& point, const Vector3& direction);

			void SetPoint(const Vector3& point);
			void SetDirection(const Vector3& direction);

			Vector3 GetPoint(void) const;
			Vector3 GetDirection(void) const;
			Vector3 GetPointOnLine(const float& scalar) const;

		private:
			Vector3 m_Point;
			Vector3 m_Direction;
		};
	}
}