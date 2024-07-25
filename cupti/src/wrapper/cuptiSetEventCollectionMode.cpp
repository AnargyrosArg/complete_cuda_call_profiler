#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiSetEventCollectionMode(CUcontext context, CUpti_EventCollectionMode mode)
{
	CUptiResult retval = cuptiSetEventCollectionMode(context, mode);
	return retval;
}