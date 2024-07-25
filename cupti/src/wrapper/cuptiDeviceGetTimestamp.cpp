#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceGetTimestamp(CUcontext context, uint64_t *timestamp)
{
	CUptiResult retval = cuptiDeviceGetTimestamp(context, timestamp);
	return retval;
}