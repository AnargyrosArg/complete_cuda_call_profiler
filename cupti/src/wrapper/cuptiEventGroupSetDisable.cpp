#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupSetDisable(CUpti_EventGroupSet *eventGroupSet)
{
	CUptiResult retval = cuptiEventGroupSetDisable(eventGroupSet);
	return retval;
}