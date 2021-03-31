#pragma once

#include <string>

class MemoryPoolHeader;

class MemoryPool
{
public:
	MemoryPool(std::string name, size_t poolSize = 0, size_t objectSize = 0);
	~MemoryPool(void);

	void*							Allocate(void);
	void								Free(void* pMemory);

	int									GetSizeUsed(void);
	int									GetSizeAllocated(void);
	int									GetPeakSizeUsed(void);
	int									GetNumberOfAllocations(void);

private:
	int									m_MaxIdValue;
	int									m_ElementSize;

	int									m_SizeUsed;
	int									m_PeakSizeUsed;
	int									m_SizeAllocated;
	int									m_NumberOfElements;

	void*							m_pMemoryHead;
	void*							m_pMemoryBlock;

	std::string						m_Name;
	MemoryPoolHeader*	m_pFreeSlot;
};