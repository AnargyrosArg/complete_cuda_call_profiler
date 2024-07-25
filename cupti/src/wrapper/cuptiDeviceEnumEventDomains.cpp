#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceEnumEventDomains(CUdevice device, size_t *arraySizeBytes, CUpti_EventDomainID *domainArray)
{
	CUptiResult retval = cuptiDeviceEnumEventDomains(device, arraySizeBytes, domainArray);
	return retval;
}