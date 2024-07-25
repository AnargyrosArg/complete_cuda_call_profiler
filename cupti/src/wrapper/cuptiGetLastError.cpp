#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetLastError()
{
	CUptiResult retval = cuptiGetLastError();
	return retval;
}