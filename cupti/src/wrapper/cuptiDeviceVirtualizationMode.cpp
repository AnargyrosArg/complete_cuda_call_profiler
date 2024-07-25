#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceVirtualizationMode(CUdevice dev, CUpti_DeviceVirtualizationMode *mode)
{
	CUptiResult retval = cuptiDeviceVirtualizationMode(dev, mode);
	return retval;
}