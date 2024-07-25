#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGroupSetAttribute(CUpti_EventGroup eventGroup, CUpti_EventGroupAttribute attrib, size_t valueSize, void *value)
{
	CUptiResult retval = cuptiEventGroupSetAttribute(eventGroup, attrib, valueSize, value);
	return retval;
}