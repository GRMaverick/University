#include "stdafx.h"
#include "Vector3.h"
#include <stdexcept>

//Vector3::Vector3(Vector3& vector){
//	x = vector.x;
//	y = vector.y;
//	z = vector.z;
//}
//Vector3::Vector3(float a, float b, float c){
//	x = a;
//	y = b;
//	z = c;
//}
Vector3::~Vector3(){

}

Vector3	Vector3::operator+(Vector3& b){
	return Vector3(x + b.x, y + b.y, z + b.z);
}
Vector3	Vector3::operator-(Vector3& b){
	return Vector3(x - b.x, y - b.y, z - b.z);
}
Vector3	Vector3::operator*(const float value){
	return Vector3(x*value, y*value, z*value);
}
float			Vector3::operator*(const Vector3& b){
	return x*b.x + y*b.y + z*b.z;
}

void			Vector3::operator+=(const Vector3& b){
	x += b.x;
	y += b.y;
	z += b.z;
}
void			Vector3::operator-=(const Vector3& b){
	x -= b.x;
	y -= b.y;
	z -= b.z;
}
void			Vector3::operator*=(const float value){
	x *= value;
	y *= value;
	z *= value;
}

void			Vector3::operator=(const Vector3& b){
	x = b.x;
	y = b.y;
	z = b.z;
}

bool			Vector3::operator==(const Vector3& b){
	if (x == b.x && y == b.y && z == b.z)
		return true;
	return false;
}
bool			Vector3::operator!=(const Vector3& b){
	return !(Vector3(x, y, z) == b);
}

void			Vector3::Invert(){
	x = -x;
	y = -y;
	z = -z;
}

float			Vector3::Magnitude(){
	return sqrt(x*x + y*y + z*z);
}
float			Vector3::SquareMagnitude(){
	return x*x + y*y + z*z;
}
float			Vector3::Dot(const Vector3& b){
	return x * b.x + y * b.y + z * b.z;
}
Vector3	Vector3::Normalise(){
	return Vector3(x / Magnitude(), y / Magnitude(), z / Magnitude());
}
Vector3	Vector3::Cross(const Vector3& b){
	return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
}