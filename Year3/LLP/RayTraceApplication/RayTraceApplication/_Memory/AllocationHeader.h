#pragma once

#define SIGNATURE_START		0xDEADC0DE
#define SIGNATURE_END			0xDEADBEEF

class IAllocator;

struct AllocationHeader
{
	int Signature;
	IAllocator* pAllocator;
	size_t Size;
};