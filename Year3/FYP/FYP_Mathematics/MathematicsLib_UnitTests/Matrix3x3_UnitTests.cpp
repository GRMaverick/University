//#include "pch.h"
#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MathematicsLib/Matrix3x3.h"

using namespace Mathematics::Structures;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Mathematics_UnitTests
{
	TEST_CLASS(Matrix3x3_UnitTest)
	{
	public:
		TEST_METHOD(Matrix3x3_DefaultConstructor)
		{
			Matrix3x3 matrix;

			Assert::AreEqual(0.0f, matrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, matrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_ElementalConstructor)
		{
			Matrix3x3 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			Assert::AreEqual(1.0f, matrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, matrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, matrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, matrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(5.0f, matrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, matrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(7.0f, matrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, matrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(9.0f, matrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_CopyConstructor)
		{
			Matrix3x3 copy;
			Matrix3x3 original(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			copy = original;

			Assert::AreEqual(1.0f, copy.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, copy.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, copy.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, copy.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(5.0f, copy.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, copy.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(7.0f, copy.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, copy.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(9.0f, copy.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_DeterminantIsZero)
		{
			// Arrange
			float determinant = 0.0f;
			Matrix3x3 vector(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			determinant = vector.Determinant();

			// Assert
			Assert::AreEqual(0.0f, determinant, L"Determinant is not ZERO", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_DeterminantIsNotZero)
		{
			// Arrange
			float determinant = 0.0f;
			Matrix3x3 vector(3.0f, 0.0f, 2.0f, 2.0f, 0.0f, -2.0f, 0.0f, 1.0f, 1.0f);

			// Act
			determinant = vector.Determinant();

			//Assert
			Assert::AreNotEqual(0.0f, determinant, L"Determinant is ZERO", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_InverseIsTrue)
		{
			// Arrange
			Matrix3x3 inverse;
			Matrix3x3 matrix(3.0f, 0.0f, 2.0f, 2.0f, 0.0f, -2.0f, 0.0f, 1.0f, 1.0f);

			// Act
			inverse = matrix.Inverse();

			// Assert
			Assert::AreEqual(0.2f, inverse.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.2f, inverse.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(-0.2f, inverse.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.3f, inverse.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(1.0f, inverse.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.2f, inverse.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(-0.3f, inverse.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_InverseIsFalse)
		{
			// Arrange
			Matrix3x3 inverse;
			Matrix3x3 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			inverse = matrix.Inverse();

			// Assert
			Assert::AreEqual(0.0f, inverse.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(0.0f, inverse.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}

		TEST_METHOD(Matrix3x3_ScalarMultiplication)
		{
			// Arrange
			float scalar = 2.0f;
			Matrix3x3 finalMatrix;
			Matrix3x3 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalMatrix = matrix * scalar;

			// Assert
			Assert::AreEqual(2.0f, finalMatrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalMatrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, finalMatrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, finalMatrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(10.0f, finalMatrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(12.0f, finalMatrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(14.0f, finalMatrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(16.0f, finalMatrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(18.0f, finalMatrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_ScalarDivision)
		{
			// Arrange
			float scalar = 2.0f;
			Matrix3x3 finalMatrix;
			Matrix3x3 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalMatrix = matrix / scalar;

			// Assert
			Assert::AreEqual(0.5f, finalMatrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(1.0f, finalMatrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(1.5f, finalMatrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, finalMatrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.5f, finalMatrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, finalMatrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.5f, finalMatrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalMatrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.5f, finalMatrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_IncrementalScalarMultiplication)
		{
			// Arrange
			float scalar = 2.0f;
			Matrix3x3 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			matrix *= scalar;

			// Assert
			Assert::AreEqual(2.0f, matrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, matrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, matrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, matrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(10.0f, matrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(12.0f, matrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(14.0f, matrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(16.0f, matrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(18.0f, matrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_IncrementalScalarDivision)
		{
			// Arrange
			float scalar = 2.0f;
			Matrix3x3 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			matrix /= scalar;

			// Assert
			Assert::AreEqual(0.5f, matrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(1.0f, matrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(1.5f, matrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, matrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.5f, matrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, matrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.5f, matrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, matrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.5f, matrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}		
		TEST_METHOD(Matrix3x3_MatrixAddition)
		{
			// Arrange
			float scalar = 2.0f;
			Matrix3x3 finalMatrix;
			Matrix3x3 leftMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
			Matrix3x3 rightMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalMatrix = leftMatrix + rightMatrix;

			// Assert
			Assert::AreEqual(2.0f, finalMatrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalMatrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, finalMatrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, finalMatrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(10.0f, finalMatrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(12.0f, finalMatrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(14.0f, finalMatrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(16.0f, finalMatrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(18.0f, finalMatrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_MatrixSubtraction)
		{
			// Arrange
			Matrix3x3 finalMatrix;
			Matrix3x3 leftMatrix(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
			Matrix3x3 rightMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalMatrix = leftMatrix - rightMatrix;

			// Assert
			Assert::AreEqual(1.0f, finalMatrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, finalMatrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, finalMatrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalMatrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(5.0f, finalMatrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, finalMatrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(7.0f, finalMatrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, finalMatrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(9.0f, finalMatrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_MatrixMultiplication)
		{
			// Arrange
			Matrix3x3 finalMatrix;
			Matrix3x3 leftMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
			Matrix3x3 rightMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalMatrix = leftMatrix * rightMatrix;

			// Assert
			Assert::AreEqual(30.0f, finalMatrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(36.0f, finalMatrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(42.0f, finalMatrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(66.0f, finalMatrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(81.0f, finalMatrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(96.0f, finalMatrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(102.0f, finalMatrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(126.0f, finalMatrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(150.0f, finalMatrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}

		TEST_METHOD(Matrix3x3_IncrementalMatrixAddition)
		{
			// Arrange
			Matrix3x3 finalMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
			Matrix3x3 rightMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalMatrix += rightMatrix;

			// Assert
			Assert::AreEqual(2.0f, finalMatrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalMatrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, finalMatrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, finalMatrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(10.0f, finalMatrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(12.0f, finalMatrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(14.0f, finalMatrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(16.0f, finalMatrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(18.0f, finalMatrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}
		TEST_METHOD(Matrix3x3_IncrementalMatrixSubtraction)
		{
			// Arrange
			Matrix3x3 finalMatrix(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
			Matrix3x3 rightMatrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalMatrix -= rightMatrix;

			// Assert
			Assert::AreEqual(1.0f, finalMatrix.row1[0], L"Element 1,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(2.0f, finalMatrix.row1[1], L"Element 1,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(3.0f, finalMatrix.row1[2], L"Element 1,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(4.0f, finalMatrix.row2[0], L"Element 2,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(5.0f, finalMatrix.row2[1], L"Element 2,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(6.0f, finalMatrix.row2[2], L"Element 2,3 Component Incorrect", LINE_INFO());
			Assert::AreEqual(7.0f, finalMatrix.row3[0], L"Element 3,1 Component Incorrect", LINE_INFO());
			Assert::AreEqual(8.0f, finalMatrix.row3[1], L"Element 3,2 Component Incorrect", LINE_INFO());
			Assert::AreEqual(9.0f, finalMatrix.row3[2], L"Element 3,3 Component Incorrect", LINE_INFO());
		}

		TEST_METHOD(Matrix3x3_VectorMultiplication)
		{
			// Arrange
			Vector3 finalVector;
			Vector3 vectorOperand(1.0f, 2.0f, 3.0f);
			Matrix3x3 matrixOperand(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

			// Act
			finalVector = Matrix3x3::VectorMultiply(vectorOperand, matrixOperand);

			// Assert
			Assert::AreEqual(14.0f, finalVector.x, L"X Component Incorrect", LINE_INFO());
			Assert::AreEqual(32.0f, finalVector.y, L"Y Component Incorrect", LINE_INFO());
			Assert::AreEqual(50.0f, finalVector.z, L"Z Component Incorrect", LINE_INFO());
		}
	};
}