#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupReadEvent(CUpti_EventGroup eventGroup, CUpti_ReadEventFlags flags, CUpti_EventID event, size_t *eventValueBufferSizeBytes, uint64_t *eventValueBuffer)
{
	CUptiResult retval = cuptiEventGroupReadEvent(eventGroup, flags, event, eventValueBufferSizeBytes, eventValueBuffer);
	return retval;
}