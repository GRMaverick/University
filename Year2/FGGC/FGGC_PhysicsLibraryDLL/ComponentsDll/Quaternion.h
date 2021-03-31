#pragma once

#ifdef COMPONENTSDLL_EXPORTS
	#define COMPONENTSDLL_API __declspec(dllexport)
#else
	#define COMPONENTSDLL_API __declspec(dllimport)
#endif

#include "Commons.h"

class Quaternion
{
public:
	float x, y, z, w;

	Quaternion() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
	Quaternion(Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; }
	Quaternion(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w; }
	~Quaternion() {	}

	COMPONENTSDLL_API inline void operator=(Quaternion second) {	x = second.x; y = second.y; z = second.z; w = second.w;  }
	COMPONENTSDLL_API inline bool operator==(Quaternion second) { return (x == second.x && y == second.y && z == second.z); }
	COMPONENTSDLL_API inline bool operator!=(Quaternion second) { return !(this == &second); }
	COMPONENTSDLL_API Quaternion operator+(Quaternion second);
	COMPONENTSDLL_API Quaternion operator-(Quaternion second);
	COMPONENTSDLL_API void operator*=(Quaternion second);

	COMPONENTSDLL_API inline float Dot(Quaternion q1, Quaternion q2);
	COMPONENTSDLL_API inline float Length() {	return (float)sqrt(w*w + x*x + y*y + z*z); }
	COMPONENTSDLL_API inline float LengthSquared() { return (float)(w*w + x*x + y*y + z*z); }

	COMPONENTSDLL_API void Normalise();

	COMPONENTSDLL_API void RotateByVector(XMFLOAT3 vector);
	
	COMPONENTSDLL_API void AddScaledVector(XMFLOAT3 vector, float scale);

private:	
};