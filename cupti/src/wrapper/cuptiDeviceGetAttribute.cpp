#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceGetAttribute(CUdevice device, CUpti_DeviceAttribute attrib, size_t *valueSize, void *value)
{
	CUptiResult retval = cuptiDeviceGetAttribute(device, attrib, valueSize, value);
	return retval;
}