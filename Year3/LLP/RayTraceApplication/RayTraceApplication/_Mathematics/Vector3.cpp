#include <assert.h>

#include "Vector3.h"
#include "AllocationHeader.h"
#include "MemoryPoolManager.h"

MemoryPool* Vector3::MemoryPool = nullptr;

Vector3::Vector3(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}
Vector3::Vector3(float xyz)
{
	this->x = xyz;
	this->y = xyz;
	this->z = xyz;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void* Vector3::operator new(size_t size)
{
	if (!MemoryPool)
		MemoryPool = MemoryPoolManager::Instance()->GetMemoryPool("Vector3", 100, size + sizeof(AllocationHeader) + sizeof(int));

	size_t requestedSize = size + sizeof(AllocationHeader) + sizeof(int);
	char* pMeme = (char*)MemoryPool->Allocate();
	AllocationHeader* pHeader = (AllocationHeader*)pMeme;

	pHeader->Signature = SIGNATURE_START;
	pHeader->Size = size;

	void* pStartMemeBlock = pMeme + sizeof(AllocationHeader);

	int* pEndMarker = (int*)((char*)pStartMemeBlock + size);
	*pEndMarker = SIGNATURE_END;

	return pStartMemeBlock;
}
void Vector3::operator delete(void* pMemory)
{
	AllocationHeader* pHeader = (AllocationHeader*)((char*)pMemory - sizeof(AllocationHeader));

	assert(pHeader->Signature == SIGNATURE_START);

	int* pEndMarker = (int*)((char*)pMemory + pHeader->Size);

	assert(*pEndMarker == SIGNATURE_END);

	MemoryPool->Free(pHeader);
}

Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator-(void) const
{
	return Vector3(-x, -y, -z);
}
Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator*(const float& scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}
Vector3 Vector3::operator*(const Vector3& vector) const
{
	return Vector3(x * vector.x, y * vector.y, z * vector.z);
}

Vector3 Vector3::operator/(const float& scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator+=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}
Vector3& Vector3::operator-=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}
Vector3& Vector3::operator*=(const Vector3& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

bool Vector3::operator==(const Vector3& vector) const
{
	return (this->x == vector.x && this->y == vector.y && this->z == vector.z);
}
bool Vector3::operator!=(const Vector3& vector) const
{
	return !(*this == vector);
}

Vector3& Vector3::Normalise(void)
{
	float normalSquare = this->LengthSquared();
	if (normalSquare > 0)
	{
		float inverseNormal = 1 / sqrt(normalSquare);

		x *= inverseNormal;
		y *= inverseNormal;
		z *= inverseNormal;
	}

	return *this;
}
Vector3 Vector3::Negate(void) const
{
	return Vector3(-x, -y, -z);
}
float Vector3::Length(void) const
{
	return sqrt(LengthSquared());
}
float Vector3::LengthSquared(void) const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}
float Vector3::Dot(const Vector3& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z;
}
