#pragma once
#include <map>
#include <typeindex>
#include <vector>

#include "MemoryPool.h"
#include "MemoryReportItem.h"

class MemoryPoolManager
{
public:
	~MemoryPoolManager(void);

	static MemoryPoolManager* Instance(void);

	void GenerateReport(std::string name);
	void ExportReport(void);

	MemoryPool* GetMemoryPool(std::string name, int objectCount, int objectSize);

private:
	static MemoryPoolManager* m_Instance;
	std::map<std::string, std::vector<MemoryReportItem>> m_Reports;
	std::map<std::string, MemoryPool*> m_MemoryPools;

	MemoryPoolManager(void);
	void PrintReportItem(MemoryReportItem item);
};