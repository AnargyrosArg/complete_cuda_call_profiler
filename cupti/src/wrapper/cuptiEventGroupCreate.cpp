#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupCreate(CUcontext context, CUpti_EventGroup *eventGroup, uint32_t flags)
{
	CUptiResult retval = cuptiEventGroupCreate(context, eventGroup, flags);
	return retval;
}