#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityDisableContext(CUcontext context, CUpti_ActivityKind kind)
{
	CUptiResult retval = cuptiActivityDisableContext(context, kind);
	return retval;
}