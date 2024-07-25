#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupRemoveAllEvents(CUpti_EventGroup eventGroup)
{
	CUptiResult retval = cuptiEventGroupRemoveAllEvents(eventGroup);
	return retval;
}