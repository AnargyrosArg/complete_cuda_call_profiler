#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupResetAllEvents(CUpti_EventGroup eventGroup)
{
	CUptiResult retval = cuptiEventGroupResetAllEvents(eventGroup);
	return retval;
}