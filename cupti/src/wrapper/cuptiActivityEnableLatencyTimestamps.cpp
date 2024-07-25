#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityEnableLatencyTimestamps(uint8_t enable)
{
	CUptiResult retval = cuptiActivityEnableLatencyTimestamps(enable);
	return retval;
}