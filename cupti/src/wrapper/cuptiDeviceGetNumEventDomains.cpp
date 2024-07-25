#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceGetNumEventDomains(CUdevice device, uint32_t *numDomains)
{
	CUptiResult retval = cuptiDeviceGetNumEventDomains(device, numDomains);
	return retval;
}