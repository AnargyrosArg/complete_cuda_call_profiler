#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGetIdFromName(CUdevice device, const char *eventName, CUpti_EventID *event)
{
	CUptiResult retval = cuptiEventGetIdFromName(device, eventName, event);
	return retval;
}