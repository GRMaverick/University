#pragma once

#include <string>

class MemoryReportItem
{
public:
	std::string		Name;
	int					SizeAllocated;
	int					SizeUtilised;
	int					PeakSizeUtilised;
	int					NumberOfAllocations;
};