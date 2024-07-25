#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupDisable(CUpti_EventGroup eventGroup)
{
	CUptiResult retval = cuptiEventGroupDisable(eventGroup);
	return retval;
}