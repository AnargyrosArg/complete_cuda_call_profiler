#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupSetEnable(CUpti_EventGroupSet *eventGroupSet)
{
	CUptiResult retval = cuptiEventGroupSetEnable(eventGroupSet);
	return retval;
}