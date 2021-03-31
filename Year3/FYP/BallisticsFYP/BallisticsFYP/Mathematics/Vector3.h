#pragma once

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3(void);
	Vector3(const float& xyz);
	Vector3(const Vector3& rhs);
	Vector3(const float& x, const float& y, const float& z);
	~Vector3(void);

	Vector3&		operator*(const float& scalar) const;
	Vector3&		operator/(const float& scalar) const;
	Vector3&		operator-(const Vector3& rhs) const;
	Vector3&		operator+(const Vector3& rhs) const;

	void				operator-=(const Vector3& rhs);
	void				operator+=(const Vector3& rhs);
	void				operator*=(const Vector3& rhs);
	void				operator/=(const Vector3& rhs);

	float				Magnitude(void) const;
	float				Dot(const Vector3& rhs) const;
	float				AngleInRadians(const Vector3& rhs) const;
	float				AngleInDegrees(const Vector3& rhs) const;

	Vector3&		Negate(void) const;
	Vector3&		Normalise(void) const;
	Vector3&		Cross(const Vector3& rhs) const;
};
