#pragma once

class MemoryPoolHeader
{
public:
	int									Id;
	MemoryPoolHeader*		pNextHeader;
	MemoryPoolHeader*		pPreviousHeader;
};
