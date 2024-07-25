#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventDomainGetNumEvents(CUpti_EventDomainID eventDomain, uint32_t *numEvents)
{
	CUptiResult retval = cuptiEventDomainGetNumEvents(eventDomain, numEvents);
	return retval;
}