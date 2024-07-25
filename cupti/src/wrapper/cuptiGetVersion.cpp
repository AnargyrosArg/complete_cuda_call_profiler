#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetVersion(uint32_t *version)
{
	CUptiResult retval = cuptiGetVersion(version);
	return retval;
}