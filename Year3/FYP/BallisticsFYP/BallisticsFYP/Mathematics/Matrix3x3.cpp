#include "pch.h"
#include "Matrix3x3.h"

Matrix3x3::Matrix3x3(void)
{
	row1[0] = 0.0f;
	row1[1] = 0.0f;
	row1[2] = 0.0f;

	row2[0] = 0.0f;
	row2[1] = 0.0f;
	row2[2] = 0.0f;

	row3[0] = 0.0f;
	row3[1] = 0.0f;
	row3[2] = 0.0f;
}
Matrix3x3::Matrix3x3(float e11, float e12, float e13, float e21, float e22, float e23, float e31, float e32, float e33)
{
	row1[0] = e11;
	row1[1] = e12;
	row1[2] = e13;

	row2[0] = e21;
	row2[1] = e22;
	row2[2] = e23;

	row3[0] = e31;
	row3[1] = e32;
	row3[2] = e33;
}
Matrix3x3::Matrix3x3(const Matrix3x3& matrix)
{
	row1[0] = matrix.row1[0];
	row1[1] = matrix.row1[1];
	row1[2] = matrix.row1[2];
	
	row2[0] = matrix.row2[0];
	row2[1] = matrix.row2[1];
	row2[2] = matrix.row2[2];

	row3[0] = matrix.row3[0];
	row3[1] = matrix.row3[1];
	row3[2] = matrix.row3[2];

}
Matrix3x3::~Matrix3x3(void)
{

}

Matrix3x3 Matrix3x3::operator+(Matrix3x3& matrix)
{
	Matrix3x3 returnMat;

	returnMat.row1[0] = row1[0] + matrix.row1[0];
	returnMat.row1[1] = row1[1] + matrix.row1[1];
	returnMat.row1[2] = row1[2] + matrix.row1[2];
												 
	returnMat.row2[0] = row2[0] + matrix.row2[0];
	returnMat.row2[1] = row2[1] + matrix.row2[1];
	returnMat.row2[2] = row2[2] + matrix.row2[2];
												 
	returnMat.row3[0] = row3[0] + matrix.row3[0];
	returnMat.row3[1] = row3[1] + matrix.row3[1];
	returnMat.row3[2] = row3[2] + matrix.row3[2];

	return returnMat;
}
Matrix3x3 Matrix3x3::operator-(Matrix3x3& matrix)
{
	Matrix3x3 returnMat;

	returnMat.row1[0] = row1[0] - matrix.row1[0];
	returnMat.row1[1] = row1[1] - matrix.row1[1];
	returnMat.row1[2] = row1[2] - matrix.row1[2];
												 
	returnMat.row2[0] = row2[0] - matrix.row2[0];
	returnMat.row2[1] = row2[1] - matrix.row2[1];
	returnMat.row2[2] = row2[2] - matrix.row2[2];
												 
	returnMat.row3[0] = row3[0] - matrix.row3[0];
	returnMat.row3[1] = row3[1] - matrix.row3[1];
	returnMat.row3[2] = row3[2] - matrix.row3[2];

	return returnMat;
}
Matrix3x3 Matrix3x3::operator*(Matrix3x3& matrix)
{
	Matrix3x3 returnMat;

	returnMat.row1[0] = row1[0] * matrix.row1[0] + row1[1] * matrix.row2[0] + row1[2] * matrix.row3[0];
	returnMat.row1[1] = row1[0] * matrix.row1[1] + row1[1] * matrix.row2[1] + row1[2] * matrix.row3[1];
	returnMat.row1[2] = row1[0] * matrix.row1[2] + row1[1] * matrix.row2[2] + row1[2] * matrix.row3[2];
	
	returnMat.row2[0] = row2[0] * matrix.row1[0] + row2[1] * matrix.row2[0] + row2[2] * matrix.row3[0];
	returnMat.row2[1] = row2[0] * matrix.row1[1] + row2[1] * matrix.row2[1] + row2[2] * matrix.row3[1];
	returnMat.row2[2] = row2[0] * matrix.row1[2] + row2[1] * matrix.row2[2] + row2[2] * matrix.row3[2];
	
	returnMat.row3[0] = row3[0] * matrix.row1[0] + row3[1] * matrix.row2[0] + row3[2] * matrix.row3[0];
	returnMat.row3[1] = row3[0] * matrix.row1[1] + row3[1] * matrix.row2[1] + row3[2] * matrix.row3[1];
	returnMat.row3[2] = row3[0] * matrix.row1[2] + row3[1] * matrix.row2[2] + row3[2] * matrix.row3[2];

	return returnMat;
}

Matrix3x3 Matrix3x3::operator*(float& scalar)
{
	Matrix3x3 returnMat;

	returnMat.row1[0] = row1[0] * scalar;
	returnMat.row1[1] = row1[1] * scalar;
	returnMat.row1[2] = row1[2] * scalar;

	returnMat.row2[0] = row2[0] * scalar;
	returnMat.row2[1] = row2[1] * scalar;
	returnMat.row2[2] = row2[2] * scalar;

	returnMat.row3[0] = row3[0] * scalar;
	returnMat.row3[1] = row3[1] * scalar;
	returnMat.row3[2] = row3[2] * scalar;

	return returnMat;
}
Matrix3x3 Matrix3x3::operator/(float& scalar)
{
	Matrix3x3 returnMat;

	returnMat.row1[0] = row1[0] / scalar;
	returnMat.row1[1] = row1[1] / scalar;
	returnMat.row1[2] = row1[2] / scalar;
												 
	returnMat.row2[0] = row2[0] / scalar;
	returnMat.row2[1] = row2[1] / scalar;
	returnMat.row2[2] = row2[2] / scalar;
												  
	returnMat.row3[0] = row3[0] / scalar;
	returnMat.row3[1] = row3[1] / scalar;
	returnMat.row3[2] = row3[2] / scalar;

	return returnMat;
}

Matrix3x3& Matrix3x3::operator+=(Matrix3x3& matrix)
{
	row1[0] += matrix.row1[0];
	row1[1] += matrix.row1[1];
	row1[2] += matrix.row1[2];
				   
	row2[0] += matrix.row2[0];
	row2[1] += matrix.row2[1];
	row2[2] += matrix.row2[2];
				   
	row3[0] += matrix.row3[0];
	row3[1] += matrix.row3[1];
	row3[2] += matrix.row3[2];

	return *this;
}
Matrix3x3& Matrix3x3::operator-=(Matrix3x3& matrix)
{
	row1[0] -= matrix.row1[0];
	row1[1] -= matrix.row1[1];
	row1[2] -= matrix.row1[2];
				 
	row2[0] -= matrix.row2[0];
	row2[1] -= matrix.row2[1];
	row2[2] -= matrix.row2[2];
				 
	row3[0] -= matrix.row3[0];
	row3[1] -= matrix.row3[1];
	row3[2] -= matrix.row3[2];

	return *this;
}

Matrix3x3& Matrix3x3::operator*=(float& scalar)
{
	row1[0] *= scalar;
	row1[1] *= scalar;
	row1[2] *= scalar;
					 
	row2[0] *= scalar;
	row2[1] *= scalar;
	row2[2] *= scalar;
					 
	row3[0] *= scalar;
	row3[1] *= scalar;
	row3[2] *= scalar;

	return *this;
}
Matrix3x3& Matrix3x3::operator/=(float& scalar)
{
	row1[0] /= scalar;
	row1[1] /= scalar;
	row1[2] /= scalar;
				 
	row2[0] /= scalar;
	row2[1] /= scalar;
	row2[2] /= scalar;
				 
	row3[0] /= scalar;
	row3[1] /= scalar;
	row3[2] /= scalar;

	return *this;
}

float Matrix3x3::Determinant(void)
{
	return (row1[0]*row2[1]*row3[2]) - (row1[0]*row3[1]*row2[2]) 
			+ (row2[0]*row3[1]*row1[2]) - (row2[0]*row1[1]*row3[2]) 
			+ (row3[0]*row1[1]*row2[2]) - (row3[0]*row2[1]*row1[2]);
}
Matrix3x3 Matrix3x3::Transpose(void)
{
	return Matrix3x3(row1[0], row2[0], row3[0], row1[1], row2[1], row3[1], row1[2], row2[2], row3[2]);
}
Matrix3x3 Matrix3x3::Inverse(void)
{
	float determinant = this->Determinant();
	if (determinant != 0)
	{
		return Matrix3x3((row2[1] * row3[2] - row2[2] * row3[1]) / determinant,
			-(row1[1] * row3[2] - row1[2] * row3[1]) / determinant,
			(row1[1] * row2[2] - row1[2] * row2[1]) / determinant,
			-(row2[0] * row3[2] - row2[2] * row3[0]) / determinant,
			(row1[0] * row3[2] - row1[2] * row3[0]) / determinant,
			-(row1[0] * row2[2] - row1[2] * row2[0]) / determinant,
			(row2[0] * row3[1] - row2[1] * row3[0]) / determinant,
			-(row1[0] * row3[1] - row1[1] * row3[0]) / determinant,
			(row1[0] * row2[1] - row1[1] * row2[0]) / determinant);
	}
	else
	{
		return Matrix3x3();
	}

}

Vector3& Matrix3x3::VectorMultiply(const Vector3& vector, const Matrix3x3& matrix)
{
	Vector3 returnVector;

	returnVector.x = matrix.row1[0] * vector.x + matrix.row1[1] * vector.y + matrix.row1[2] * vector.z;
	returnVector.y = matrix.row2[0] * vector.x + matrix.row2[1] * vector.y + matrix.row2[2] * vector.z;
	returnVector.z = matrix.row3[0] * vector.x + matrix.row3[1] * vector.y + matrix.row3[2] * vector.z;

	return returnVector;
}