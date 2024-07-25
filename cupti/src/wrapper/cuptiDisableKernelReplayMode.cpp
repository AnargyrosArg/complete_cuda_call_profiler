#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDisableKernelReplayMode(CUcontext context)
{
	CUptiResult retval = cuptiDisableKernelReplayMode(context);
	return retval;
}