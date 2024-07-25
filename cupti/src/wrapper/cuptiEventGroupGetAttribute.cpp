#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupGetAttribute(CUpti_EventGroup eventGroup, CUpti_EventGroupAttribute attrib, size_t *valueSize, void *value)
{
	CUptiResult retval = cuptiEventGroupGetAttribute(eventGroup, attrib, valueSize, value);
	return retval;
}