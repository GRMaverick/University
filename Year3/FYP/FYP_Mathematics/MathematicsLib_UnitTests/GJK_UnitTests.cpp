#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "../MathematicsLib/Vector3.h"
#include "../MathematicsLib/NarrowPhaseCollisionDetection.h"

using namespace Mathematics::Structures;
using namespace Mathematics::Intersections;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Mathematics_UnitTests
{
	TEST_CLASS(GJK_UnitTest)
	{
	public:
		TEST_METHOD(GJK_Failed)
		{
			// Arrange
			Vector3 position(3.0f, 3.0f, 3.0f);

			std::vector<Vector3> aObjectVertices;
			aObjectVertices.push_back(Vector3(-1, -1, -1));		// Front
			aObjectVertices.push_back(Vector3(1, -1, -1));
			aObjectVertices.push_back(Vector3(-1, 1, -1));
			aObjectVertices.push_back(Vector3(1, 1, -1));
			aObjectVertices.push_back(Vector3(1, 1, 1));			// Back
			aObjectVertices.push_back(Vector3(1, -1, 1));
			aObjectVertices.push_back(Vector3(-1, 1, 1));
			aObjectVertices.push_back(Vector3(-1, -1, 1));

			std::vector<Vector3> bObjectVertices;
			bObjectVertices.push_back(position + Vector3(-1, -1, -1));		// Front
			bObjectVertices.push_back(position + Vector3(1, -1, -1));
			bObjectVertices.push_back(position + Vector3(-1, 1, -1));
			bObjectVertices.push_back(position + Vector3(1, 1, -1));
			bObjectVertices.push_back(position + Vector3(1, 1, 1));			// Back
			bObjectVertices.push_back(position + Vector3(1, -1, 1));
			bObjectVertices.push_back(position + Vector3(-1, 1, 1));
			bObjectVertices.push_back(position + Vector3(-1, -1, 1));

			// Act
			bool isCollisionDetected = NarrowPhaseCollisionDetection::GJKAlgorithm(aObjectVertices, bObjectVertices);

			// Assert
			Assert::IsFalse(isCollisionDetected);
		}
		TEST_METHOD(GJK_Succeeded)
		{
			// Arrange
			Vector3 position(2.0f, 2.0f, 2.0f);

			std::vector<Vector3> aObjectVertices;
			aObjectVertices.push_back(Vector3(-1, -1, -1));		// Front
			aObjectVertices.push_back(Vector3(1, -1, -1));
			aObjectVertices.push_back(Vector3(-1, 1, -1));
			aObjectVertices.push_back(Vector3(1, 1, -1));
			aObjectVertices.push_back(Vector3(1, 1, 1));			// Back
			aObjectVertices.push_back(Vector3(1, -1, 1));
			aObjectVertices.push_back(Vector3(-1, 1, 1));
			aObjectVertices.push_back(Vector3(-1, -1, 1));

			std::vector<Vector3> bObjectVertices;
			bObjectVertices.push_back(position + Vector3(-1, -1, -1));		// Front
			bObjectVertices.push_back(position + Vector3(1, -1, -1));
			bObjectVertices.push_back(position + Vector3(-1, 1, -1));
			bObjectVertices.push_back(position + Vector3(1, 1, -1));
			bObjectVertices.push_back(position + Vector3(1, 1, 1));			// Back
			bObjectVertices.push_back(position + Vector3(1, -1, 1));
			bObjectVertices.push_back(position + Vector3(-1, 1, 1));
			bObjectVertices.push_back(position + Vector3(-1, -1, 1));

			// Act
			bool isCollisionDetected = NarrowPhaseCollisionDetection::GJKAlgorithm(aObjectVertices, bObjectVertices);

			// Assert
			Assert::IsTrue(isCollisionDetected);
		}
	};
}