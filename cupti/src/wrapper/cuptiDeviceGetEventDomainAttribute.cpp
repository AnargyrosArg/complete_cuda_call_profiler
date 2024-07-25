#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceGetEventDomainAttribute(CUdevice device, CUpti_EventDomainID eventDomain, CUpti_EventDomainAttribute attrib, size_t *valueSize, void *value)
{
	CUptiResult retval = cuptiDeviceGetEventDomainAttribute(device, eventDomain, attrib, valueSize, value);
	return retval;
}