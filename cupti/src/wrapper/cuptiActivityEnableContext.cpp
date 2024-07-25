#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityEnableContext(CUcontext context, CUpti_ActivityKind kind)
{
	CUptiResult retval = cuptiActivityEnableContext(context, kind);
	return retval;
}