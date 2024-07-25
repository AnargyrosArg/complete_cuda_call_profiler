#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupSetsDestroy(CUpti_EventGroupSets *eventGroupSets)
{
	CUptiResult retval = cuptiEventGroupSetsDestroy(eventGroupSets);
	return retval;
}