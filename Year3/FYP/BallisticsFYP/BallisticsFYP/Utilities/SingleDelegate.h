#pragma once

template<typename RType, typename... PType>
class SingleDelegate
{
	typedef RType(*Type)(void* callee, PType...);

public:
	SingleDelegate()
	{
		fpCallee = nullptr;
		fpCallbackFunction = Type();
	}
	SingleDelegate(void* callee, Type function) : fpCallee(callee), fpCallbackFunction(function)
	{

	}

	template <class T, RType(T::*TMethod)(PType...)>
	static SingleDelegate FromFunction(T* callee)
	{
		SingleDelegate d(callee, &MethodCaller<T, TMethod>);
		return d;
	}

	RType operator()(PType... params) const
	{
		return (*fpCallbackFunction)(fpCallee, params...);
	}
	bool operator==(const SingleDelegate& other) const
	{
		return (fpCallee == other.fpCallee) && (fpCallbackFunction == other.fpCallbackFunction);
	}

private:
	void* fpCallee;
	Type fpCallbackFunction;

	template <class T, RType(T::*TMethod)(PType...)>
	static RType MethodCaller(void* callee, PType... params)
	{
		T* p = static_cast<T*>(callee);
		return (p->*TMethod)(params...);
	}
};