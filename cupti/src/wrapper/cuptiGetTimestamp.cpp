#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetTimestamp(uint64_t *timestamp)
{
	CUptiResult retval = cuptiGetTimestamp(timestamp);
	return retval;
}