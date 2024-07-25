#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupSetsCreate(CUcontext context, size_t eventIdArraySizeBytes, CUpti_EventID *eventIdArray, CUpti_EventGroupSets **eventGroupPasses)
{
	CUptiResult retval = cuptiEventGroupSetsCreate(context, eventIdArraySizeBytes, eventIdArray, eventGroupPasses);
	return retval;
}