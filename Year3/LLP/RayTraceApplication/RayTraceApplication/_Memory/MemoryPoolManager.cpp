
#include <fstream>
#include <iostream>
#include "RTAParameters.h"
#include "MemoryPoolManager.h"

MemoryPoolManager* MemoryPoolManager::m_Instance = nullptr;

MemoryPoolManager::MemoryPoolManager(void)
{
	m_MemoryPools.clear();
}
MemoryPoolManager::~MemoryPoolManager(void)
{
	for (auto iter = m_MemoryPools.begin(); iter != m_MemoryPools.end(); iter++)
	{
		delete iter->second;
	}

	m_MemoryPools.clear();
}

MemoryPoolManager* MemoryPoolManager::Instance(void)
{
	if (!m_Instance)
	{
		m_Instance = new MemoryPoolManager();
	}
	return m_Instance;
}

void MemoryPoolManager::GenerateReport(std::string name)
{
	std::map<std::string, MemoryPool*>::iterator iterator = m_MemoryPools.begin();

	m_Reports[name] = std::vector<MemoryReportItem>();
	for (; iterator != m_MemoryPools.end(); iterator++)
	{
		MemoryReportItem item;
		item.Name = iterator->first;
		item.SizeUtilised = iterator->second->GetSizeUsed();
		item.SizeAllocated = iterator->second->GetSizeAllocated();
		item.PeakSizeUtilised = iterator->second->GetPeakSizeUsed();
		item.NumberOfAllocations = iterator->second->GetNumberOfAllocations();
		m_Reports[name].push_back(item);

#ifdef _DEBUG
		PrintReportItem(item);
#endif
	}
}
void MemoryPoolManager::ExportReport()
{
	this->GenerateReport("Frame_" + std::to_string(RTAParameters::MaxFrames+1));

	for (auto it = m_Reports.begin(); it != m_Reports.end(); it++)
	{
		std::ofstream ofs(std::string(RTAParameters::ReportPath + "Memory\\Memory" + it->first + ".csv").c_str(), std::ofstream::out);
		if (ofs.is_open())
		{
			ofs << "NAME\tSIZE_ALLOCATED\tSIZE_USED\tPEAK_SIZE_USED\tNUMBER_OF_OBJECTS_PRESENT" << std::endl;
			for (MemoryReportItem mri : it->second)
			{
				ofs << mri.Name << "\t" << mri.SizeAllocated << "\t" << mri.SizeUtilised << "\t" << mri.PeakSizeUtilised << "\t" << mri.NumberOfAllocations << std::endl;
			}
			ofs.close();
		}
		else
		{
			std::cout << std::string(RTAParameters::ReportPath + "Memory\\Memory" + it->first + ".csv").c_str() << ": File IO FAILED!" << std::endl;
			return;
		}
	}
}

void MemoryPoolManager::PrintReportItem(MemoryReportItem item)
{
	std::cout << "Memory Pool Manager: " << std::endl;
	std::cout << " >> " << item.Name << " MemoryPool " << std::endl;
	std::cout << "		- Size Allocated: " << item.SizeAllocated << std::endl;
	std::cout << "		- Size Used: " << item.SizeUtilised << std::endl;
	std::cout << "		- Peak Size Used: " << item.PeakSizeUtilised << std::endl;
	std::cout << "		- Number of Allocations: " << item.NumberOfAllocations << std::endl;
}

MemoryPool* MemoryPoolManager::GetMemoryPool(std::string name, int objectCount, int objectSize)
{
	if (!m_MemoryPools[name])
	{
		m_MemoryPools[name] = new MemoryPool(name, objectCount, objectSize);
	}
	return m_MemoryPools[name];
}