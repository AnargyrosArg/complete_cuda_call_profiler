#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEnableKernelReplayMode(CUcontext context)
{
	CUptiResult retval = cuptiEnableKernelReplayMode(context);
	return retval;
}