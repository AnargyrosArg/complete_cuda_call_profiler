#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetNumEventDomains(uint32_t *numDomains)
{
	CUptiResult retval = cuptiGetNumEventDomains(numDomains);
	return retval;
}