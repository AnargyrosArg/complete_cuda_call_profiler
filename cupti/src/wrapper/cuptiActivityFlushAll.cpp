#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityFlushAll(uint32_t flag)
{
	CUptiResult retval = cuptiActivityFlushAll(flag);
	return retval;
}