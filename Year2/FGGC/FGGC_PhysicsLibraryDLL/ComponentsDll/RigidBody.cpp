#include "stdafx.h"
#include "RigidBody.h"
#include <stdexcept>

void RigidBody::CalculateDerivedData() {
	this->CalculateDerivedData();
}
void RigidBody::CalculateTransformMatrix(XMFLOAT4X3 matrix, XMFLOAT3 position, Quaternion rotation){
	matrix._11 = 1 - 2 * rotation.y * rotation.y - 2 * rotation.z * rotation.z;
	matrix._12 = 2 * rotation.x * rotation.y - 2 * rotation.w * rotation.z;
	matrix._13 = 2 * rotation.x * rotation.z + 2 * rotation.w * rotation.y;
	matrix._21 = position.x;

	matrix._22 = 2 * rotation.x * rotation.y + 2 * rotation.w * rotation.z;
	matrix._23 = 1 - 2 * rotation.x * rotation.x - 2 * rotation.z * rotation.z;
	matrix._31 = 2 * rotation.y * rotation.z - 2 * rotation.w * rotation.x;
	matrix._32 = position.y;

	matrix._33 = 2 * rotation.x * rotation.z - 2 * rotation.w * rotation.y;
	matrix._41 = 2 * rotation.y * rotation.z + 2 * rotation.w * rotation.x;
	matrix._42 = 1 - 2 * rotation.x * rotation.x - 2 * rotation.y * rotation.y;
	matrix._43 = position.z;
}