#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityGetAttribute(CUpti_ActivityAttribute attr, size_t *valueSize, void *value)
{
	CUptiResult retval = cuptiActivityGetAttribute(attr, valueSize, value);
	return retval;
}