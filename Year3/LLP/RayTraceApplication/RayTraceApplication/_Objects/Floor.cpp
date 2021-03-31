#include <assert.h>

#include "AllocationHeader.h"
#include "MemoryPool.h"
#include "MemoryPoolManager.h"

#include "Floor.h"

MemoryPool* Floor::MemoryPool = nullptr;

Floor::Floor(void)
{
	Mass = 0.0f;
	Center = Vector3(0);
	Extents = Vector3(0);
}
Floor::Floor(Vector3 center, Vector3 extents, float mass)
{
	Mass = mass;
	Center = center;
	Extents = extents;
}
Floor::~Floor(void)
{

}

void* Floor::operator new(size_t size)
{
	if (!MemoryPool)
		MemoryPool = MemoryPoolManager::Instance()->GetMemoryPool("Floor", 10, sizeof(Floor) + sizeof(AllocationHeader) + sizeof(int));

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
void Floor::operator delete(void* pMemory)
{
	AllocationHeader* pHeader = (AllocationHeader*)((char*)pMemory - sizeof(AllocationHeader));

	assert(pHeader->Signature == SIGNATURE_START);

	int* pEndMarker = (int*)((char*)pMemory + pHeader->Size);

	assert(*pEndMarker == SIGNATURE_END);

	MemoryPool->Free(pHeader);
}