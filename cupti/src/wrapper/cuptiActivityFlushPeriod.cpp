#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityFlushPeriod(uint32_t time)
{
	CUptiResult retval = cuptiActivityFlushPeriod(time);
	return retval;
}