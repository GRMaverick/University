#include "stdafx.h"
#include "Quaternion.h"
#include <stdexcept>

Quaternion Quaternion::operator+(Quaternion second){
	return Quaternion(this->x + second.x, this->y + second.y, this->z + second.z, this->w + second.w);
}
Quaternion Quaternion::operator-(Quaternion second){
	return Quaternion(this->x - second.x, this->y - second.y, this->z - second.z, this->w - second.w);
}
void Quaternion::operator*=(Quaternion second) {
	Quaternion q = *this;
	w = q.w*second.w - q.x*second.x - q.y*second.y - q.z*second.z;
	x = q.w*second.x + q.x*second.w + q.y*second.z - q.z*second.y;
	y = q.w*second.y + q.y*second.w + q.z*second.x - q.x*second.z;
	z = q.w*second.z + q.z*second.w + q.x*second.y - q.y*second.x;
}

void Quaternion::Normalise() {
	float length = w*w + x*x + y*y + z*z;

	if (length == 0)
	{
		w = 1.0f;
		return;
	}

	length = ((float) 1.0f) / sqrtf(length);

	w *= length;
	x *= length;
	y *= length;
	z *= length;
}
void Quaternion::RotateByVector(XMFLOAT3 vector) {
	Quaternion q = Quaternion(vector.x, vector.y, vector.z, 0.0);
	(*this) *= q;
}
void Quaternion::AddScaledVector(XMFLOAT3 vector, float scale) {
	Quaternion q = Quaternion(vector.x*scale, vector.y*scale, vector.z*scale, 0.0f);

	q *= *this;

	w += q.w * 0.5f;
	x += q.x * 0.5f;
	y += q.y * 0.5f;
	z += q.z * 0.5f;
}