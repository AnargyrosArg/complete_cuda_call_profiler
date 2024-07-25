#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityEnable(CUpti_ActivityKind kind)
{
	CUptiResult retval = cuptiActivityEnable(kind);
	return retval;
}