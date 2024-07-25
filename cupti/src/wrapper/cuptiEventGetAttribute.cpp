#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEventGetAttribute(CUpti_EventID event, CUpti_EventAttribute attrib, size_t *valueSize, void *value)
{
	CUptiResult retval = cuptiEventGetAttribute(event, attrib, valueSize, value);
	return retval;
}