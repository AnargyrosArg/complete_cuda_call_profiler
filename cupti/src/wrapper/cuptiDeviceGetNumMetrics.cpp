#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceGetNumMetrics(CUdevice device, uint32_t *numMetrics)
{
	CUptiResult retval = cuptiDeviceGetNumMetrics(device, numMetrics);
	return retval;
}