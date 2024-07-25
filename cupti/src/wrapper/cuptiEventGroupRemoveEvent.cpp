#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupRemoveEvent(CUpti_EventGroup eventGroup, CUpti_EventID event)
{
	CUptiResult retval = cuptiEventGroupRemoveEvent(eventGroup, event);
	return retval;
}