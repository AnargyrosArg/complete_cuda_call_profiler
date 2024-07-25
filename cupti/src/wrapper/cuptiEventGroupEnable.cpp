#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupEnable(CUpti_EventGroup eventGroup)
{
	CUptiResult retval = cuptiEventGroupEnable(eventGroup);
	return retval;
}