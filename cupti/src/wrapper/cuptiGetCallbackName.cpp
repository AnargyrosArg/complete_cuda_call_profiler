#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetCallbackName(CUpti_CallbackDomain domain, uint32_t cbid, const char **name)
{
	CUptiResult retval = cuptiGetCallbackName(domain, cbid, name);
	return retval;
}