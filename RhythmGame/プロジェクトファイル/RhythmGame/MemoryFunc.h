#pragma once
#include"Object.h"

class MemoryFunction {
public:
	template<typename T>
	static void check_mem(T*);//メモリ確保できたか
	//template<typename T>
	//static void create_mem(T&);//メモリ確保
	//template<typename T>
	//static void delete_mem(T&);
	//template<typename T,typename M>
	//static void run_action(T*,M(*func)());
};

template<typename T>
void MemoryFunction::check_mem(T* obj)
{
	if (obj == nullptr)throw"Object is nullptr";
}
