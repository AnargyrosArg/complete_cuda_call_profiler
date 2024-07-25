#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupDestroy(CUpti_EventGroup eventGroup)
{
	CUptiResult retval = cuptiEventGroupDestroy(eventGroup);
	return retval;
}