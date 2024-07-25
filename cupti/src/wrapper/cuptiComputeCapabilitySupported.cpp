#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiComputeCapabilitySupported(int major, int minor, int *support)
{
	CUptiResult retval = cuptiComputeCapabilitySupported(major, minor, support);
	return retval;
}