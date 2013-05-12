#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <typename Type> class CSingleton
{
public:
	static Type& GetInstance()
	{
		static Type Instance;
		return Instance;
	}
};

template <typename Type, typename DependantType> class CDependantSingleton
{
public:
	static Type& GetInstance()
	{
		static Type Instance(DependantType::GetInstance());
		return Instance;
	}
};

#endif
