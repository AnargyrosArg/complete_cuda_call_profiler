#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupAddEvent(CUpti_EventGroup eventGroup, CUpti_EventID event)
{
	CUptiResult retval = cuptiEventGroupAddEvent(eventGroup, event);
	return retval;
}