#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupReadAllEvents(CUpti_EventGroup eventGroup, CUpti_ReadEventFlags flags, size_t *eventValueBufferSizeBytes, uint64_t *eventValueBuffer, size_t *eventIdArraySizeBytes, CUpti_EventID *eventIdArray, size_t *numEventIdsRead)
{
	CUptiResult retval = cuptiEventGroupReadAllEvents(eventGroup, flags, eventValueBufferSizeBytes, eventValueBuffer, eventIdArraySizeBytes, eventIdArray, numEventIdsRead);
	return retval;
}