#include <cstdlib>
#include <assert.h>
#include <iostream>
#include <Windows.h>

#include "MemoryPool.h"
#include "MemoryPoolHeader.h"

MemoryPool::MemoryPool(std::string name, size_t poolSize, size_t objectSize)
{
	m_Name = name;

	m_SizeUsed = 0;
	m_MaxIdValue = 1;
	m_PeakSizeUsed = 0;
	m_NumberOfElements = 0;
	m_ElementSize = objectSize;
	m_SizeAllocated = poolSize * (m_ElementSize + sizeof(MemoryPoolHeader));

	m_pMemoryBlock = malloc(poolSize * (m_ElementSize + sizeof(MemoryPoolHeader)));

	m_pFreeSlot = (MemoryPoolHeader*)m_pMemoryBlock;
	m_pFreeSlot->Id = m_MaxIdValue;
	m_pFreeSlot->pNextHeader = nullptr;
	m_pFreeSlot->pPreviousHeader = nullptr;

	m_MaxIdValue++;
}
MemoryPool::~MemoryPool(void)
{
	assert(m_SizeUsed == 0 && m_NumberOfElements == 0);

	ZeroMemory(m_pMemoryBlock, sizeof(m_pMemoryBlock));
	delete m_pMemoryBlock;
}

void*		MemoryPool::Allocate(void)
{
	m_NumberOfElements++;
	m_SizeUsed += m_ElementSize;

	if (m_SizeUsed > m_PeakSizeUsed)
		m_PeakSizeUsed = m_SizeUsed;

	void* pMem = m_pFreeSlot + sizeof(MemoryPoolHeader);

	if (m_pFreeSlot->pNextHeader)
	{
#ifdef _DEBUG
		std::cout << m_Name << ": Reallocation at Element " << m_pFreeSlot->Id << std::endl;
#endif

		m_pFreeSlot = m_pFreeSlot->pNextHeader;
	}
	else
	{
#ifdef _DEBUG
		std::cout << m_Name <<  ": Allocation at Element " << m_pFreeSlot->Id << std::endl;
#endif

		m_pFreeSlot = (MemoryPoolHeader*)m_pFreeSlot + (m_ElementSize + sizeof(MemoryPoolHeader));
		m_pFreeSlot->Id = m_MaxIdValue;
		m_pFreeSlot->pNextHeader = nullptr;
		m_pFreeSlot->pPreviousHeader = nullptr;
		m_MaxIdValue++;
	}

	return pMem;
}
void		MemoryPool::Free(void* pMemory)
{
	MemoryPoolHeader* pCurrentHeader = (MemoryPoolHeader*)pMemory - sizeof(MemoryPoolHeader);
	pCurrentHeader->pNextHeader = m_pFreeSlot;
	m_pFreeSlot = pCurrentHeader;

#ifdef _DEBUG
	std::cout << m_Name << ": Deallocation at Element " << m_pFreeSlot->Id << std::endl;
#endif

	ZeroMemory(pMemory, m_ElementSize);

	m_NumberOfElements--;
	m_SizeUsed -= m_ElementSize;
}

int			MemoryPool::GetSizeUsed(void)
{
	return m_SizeUsed;
}
int			MemoryPool::GetSizeAllocated(void)
{
	return m_SizeAllocated;
}
int			MemoryPool::GetPeakSizeUsed(void)
{
	return m_PeakSizeUsed;
}
int			MemoryPool::GetNumberOfAllocations(void)
{
	return m_NumberOfElements;
}