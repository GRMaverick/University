//#include "pch.h"
#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MathematicsLib/Quaternion.h"

using namespace Mathematics::Structures;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Mathematics_UnitTests
{
	TEST_CLASS(Quaternion_UnitTest)
	{
	public:
		TEST_METHOD(Quaternion_DefaultConstructor)
		{
			// Arrange
			// Act
			Quaternion quaternion;

			// Assert
			Assert::AreEqual(0.0f, quaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, quaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, quaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(1.0f, quaternion.w, L"W Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Quaternion_CopyConstructor)
		{
			// Arrange 
			Quaternion quaternionA(2.0f, 2.0f, 2.0f, 2.0f);
			Quaternion finalQuaternion(1.0f, 1.0f, 1.0f, 1.0f);

			// Act
			finalQuaternion = quaternionA;

			// Assert
			Assert::AreEqual(2.0f, finalQuaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, finalQuaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, finalQuaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, finalQuaternion.w, L"W Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Quaternion_VectorScalarConstructor)
		{
			// Arrange 
			// Act
			Quaternion quaternion(Vector3(1.0f, 2.0f, 3.0f), 4.0f);

			// Assert
			Assert::AreEqual(1.0f, quaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, quaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, quaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, quaternion.w, L"W Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Quaternion_ComponentWiseConstructor)
		{
			// Arrange
			// Act	
			Quaternion quaternion(1.0f, 2.0f, 3.0f, 4.0f);

			// Assert
			Assert::AreEqual(1.0f, quaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, quaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, quaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, quaternion.w, L"W Component Incorrect", LINE_INFO());
		}

		TEST_METHOD(Quaternion_QuaternionMultiplication)
		{
			// Arrange
			Quaternion aQuaternion(1.0f, 1.0f, 1.0f, 1.0f);
			Quaternion bQuaternion(2.0f, 2.0f, 2.0f, 2.0f);
			Quaternion finalQuaternion;

			// Act
			finalQuaternion = aQuaternion * bQuaternion;

			// Asssert
			Assert::AreEqual(4.0f, finalQuaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalQuaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalQuaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(-4.0f, finalQuaternion.w, L"W Component Incorrect", LINE_INFO());
		}

		TEST_METHOD(Quaternion_IncrementalAddition)
		{
			// Arrange
			Quaternion quaternion(1.0f, 2.0f, 3.0f, 4.0f);
			Quaternion finalQuaternion(5.0f, 6.0f, 7.0f, 8.0f);

			// Act
			finalQuaternion += quaternion;

			// Assert
			Assert::AreEqual(6.0f, finalQuaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, finalQuaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(10.0f, finalQuaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(12.0f, finalQuaternion.w, L"W Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Quaternion_IncrementalSubtraction)
		{
			// Arrange
			Quaternion quaternion(1.0f, 2.0f, 3.0f, 4.0f);
			Quaternion finalQuaternion(5.0f, 6.0f, 7.0f, 8.0f);

			// Act
			finalQuaternion -= quaternion;

			// Assert
			Assert::AreEqual(4.0f, finalQuaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalQuaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalQuaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalQuaternion.w, L"W Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Quaternion_IncrementalQuaternionMultiplication)
		{
			// Arrange
			Quaternion finalQuaternion(1.0f, 1.0f, 1.0f, 1.0f);
			Quaternion aQuaternion(2.0f, 2.0f, 2.0f, 2.0f);

			// Act
			finalQuaternion *= aQuaternion;

			// Asssert
			Assert::AreEqual(4.0f, finalQuaternion.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalQuaternion.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalQuaternion.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(-4.0f, finalQuaternion.w, L"W Component Incorrect", LINE_INFO());
		}

		TEST_METHOD(Quaternion_Conjugate)
		{
			// Arrange
			Quaternion conjugate;
			Quaternion quaternion(5.0f, 6.0f, 7.0f, 8.0f);

			// Act
			conjugate = quaternion.Conjugate();

			// Assert
			Assert::AreEqual(-5.0f, conjugate.vector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(-6.0f, conjugate.vector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(-7.0f, conjugate.vector.z, L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, conjugate.w, L"W Component Incorrect", LINE_INFO());
		}
		//TEST_METHOD(Quaternion_Normalise)
		//{
		//	Assert::IsTrue(false);
		//}
		//TEST_METHOD(Quaternion_RotateByVector)
		//{
		//	Assert::IsTrue(false);
		//}
		TEST_METHOD(Quaternion_FromEuler)
		{
			// Arrange
			Quaternion quat = Quaternion();
			Vector3 eulerAngles = Vector3(30.0f, 60.0f, 45.0f);

			// Act
			quat.FromEuler(eulerAngles);

			Assert::AreEqual(0.391903f, RoundToNDecimalPlaces(quat.vector.x, 6),		L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.360423f,	RoundToNDecimalPlaces(quat.vector.y, 6),	L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.439679f, RoundToNDecimalPlaces(quat.vector.z, 6),		L"Z Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.723318f,	RoundToNDecimalPlaces(quat.w, 6),				L"W Component Incorrect", LINE_INFO());
		}
		//TEST_METHOD(Quaternion_ToEuler)
		//{
		//	// Arrange
		//	Quaternion quat = Quaternion(0.391903f, 0.360423f, 0.439679f, 0.723318f);
		//	Vector3 eulerAngles;

		//	// Act
		//	eulerAngles = quat.ToEuler();

		//	Assert::AreEqual(29.99f, RoundToNDecimalPlaces(eulerAngles.x, 2), L"X Component Incorrect", LINE_INFO());
		//	Assert::AreEqual(59.99f, RoundToNDecimalPlaces(eulerAngles.y, 2), L"Y Component Incorrect", LINE_INFO());
		//	Assert::AreEqual(44.99f, RoundToNDecimalPlaces(eulerAngles.z, 2), L"Z Component Incorrect", LINE_INFO());
		//}

		private:
			float RoundToNDecimalPlaces(float target, int decimalPlaces)
			{
				return floorf(target * pow(10, decimalPlaces) + 0.5) / pow(10, decimalPlaces);
			}
	};
}