#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEnumEventDomains(size_t *arraySizeBytes, CUpti_EventDomainID *domainArray)
{
	CUptiResult retval = cuptiEnumEventDomains(arraySizeBytes, domainArray);
	return retval;
}