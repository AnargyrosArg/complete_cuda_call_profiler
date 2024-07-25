#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceSupported(CUdevice dev, int *support)
{
	CUptiResult retval = cuptiDeviceSupported(dev, support);
	return retval;
}