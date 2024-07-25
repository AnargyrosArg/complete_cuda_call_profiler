#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventDomainEnumEvents(CUpti_EventDomainID eventDomain, size_t *arraySizeBytes, CUpti_EventID *eventArray)
{
	CUptiResult retval = cuptiEventDomainEnumEvents(eventDomain, arraySizeBytes, eventArray);
	return retval;
}