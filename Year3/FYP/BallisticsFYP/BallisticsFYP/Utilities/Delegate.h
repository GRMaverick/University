#pragma once

#include <vector>
#include "SingleDelegate.h"

template<typename RType, typename... PType>
class Delegate
{
public:
	Delegate(void)
	{

	}
	void operator+=(const SingleDelegate<RType, PType...>& delegate)
	{
		m_RegisteredCallbacks.push_back(delegate);
	}
	RType operator()(PType... params) const
	{
		for (SingleDelegate<RType, PType...> delegate : m_RegisteredCallbacks)
		{
			delegate(params...);
		}
	}
private:
	std::vector<SingleDelegate<RType, PType...>> m_RegisteredCallbacks;
};