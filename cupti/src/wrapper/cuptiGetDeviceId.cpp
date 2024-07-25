#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetDeviceId(CUcontext context, uint32_t *deviceId)
{
	CUptiResult retval = cuptiGetDeviceId(context, deviceId);
	return retval;
}