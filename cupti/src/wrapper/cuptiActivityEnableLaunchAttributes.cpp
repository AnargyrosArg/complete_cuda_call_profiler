#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityEnableLaunchAttributes(uint8_t enable)
{
	CUptiResult retval = cuptiActivityEnableLaunchAttributes(enable);
	return retval;
}