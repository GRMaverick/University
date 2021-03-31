#pragma once
#include "Delegate.h"

template <typename T, typename RType, typename... PType>
class DelegateFactory
{
public:
	template<RType(T::*TMethod)(PType...)>
	static RType MethodCaller(void* callee, PType... params)
	{
		return (static_cast<T*>(callee)->*TMethod)(params...);
	}

	template<RType(T::*TMethod)(PType...)>
	inline static SingleDelegate<RType, PType...> Bind(T* callee)
	{
		return SingleDelegate<RType, PType...>(callee, &DelegateFactory::MethodCaller<TMethod>);
	}
};

template<typename T, typename RType, typename... PType>
DelegateFactory<T, RType, PType...> MakeDelegate(RType(T::*)(PType...))
{
	return DelegateFactory<T, RType, PType...>();
}

#define DELEGATE(TMethod, Caller) (MakeDelegate(TMethod).Bind<TMethod>(Caller))