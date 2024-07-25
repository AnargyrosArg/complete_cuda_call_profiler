#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiKernelReplaySubscribeUpdate(CUpti_KernelReplayUpdateFunc updateFunc, void *customData)
{
	CUptiResult retval = cuptiKernelReplaySubscribeUpdate(updateFunc, customData);
	return retval;
}