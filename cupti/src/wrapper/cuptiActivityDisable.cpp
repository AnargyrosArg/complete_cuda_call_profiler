#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityDisable(CUpti_ActivityKind kind)
{
	CUptiResult retval = cuptiActivityDisable(kind);
	return retval;
}