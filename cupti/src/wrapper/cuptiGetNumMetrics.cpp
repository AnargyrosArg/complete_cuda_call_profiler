#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetNumMetrics(uint32_t *numMetrics)
{
	CUptiResult retval = cuptiGetNumMetrics(numMetrics);
	return retval;
}