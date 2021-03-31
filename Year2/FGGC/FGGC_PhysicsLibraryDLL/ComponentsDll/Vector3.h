#pragma once

#ifdef COMPONENTSDLL_EXPORTS
#define COMPONENTSDLL_API __declspec(dllexport)
#else
#define COMPONENTSDLL_API __declspec(dllimport)
#endif

#include "Commons.h"
#include "DirectXMath.h"

class Vector3 : public XMFLOAT3
{
public:
	Vector3() : XMFLOAT3(0.0f,  0.0f, 0.0f) { }
	Vector3(Vector3& vector) : XMFLOAT3(vector.x, vector.y, vector.z) { }
	Vector3(float _x, float _y, float _z) : XMFLOAT3(_x, _y, _z) { }
	~Vector3();

	COMPONENTSDLL_API Vector3 operator+(Vector3& b);
	COMPONENTSDLL_API Vector3 operator-(Vector3& b);
	COMPONENTSDLL_API Vector3 operator*(const float value);
	COMPONENTSDLL_API float		operator*(const Vector3& b);

	COMPONENTSDLL_API void		operator+=(const Vector3& b);
	COMPONENTSDLL_API void		operator-=(const Vector3& b);
	COMPONENTSDLL_API void		operator*=(const float value);

	COMPONENTSDLL_API void		operator=(const Vector3& b);

	COMPONENTSDLL_API bool		operator==(const Vector3& b);
	COMPONENTSDLL_API bool		operator!=(const Vector3& b);

	COMPONENTSDLL_API void		Invert();

	COMPONENTSDLL_API float		Magnitude();
	COMPONENTSDLL_API float		SquareMagnitude();
	COMPONENTSDLL_API float		Dot(const Vector3& b);
	COMPONENTSDLL_API Vector3 Normalise();
	COMPONENTSDLL_API Vector3 Cross(const Vector3& b);
};