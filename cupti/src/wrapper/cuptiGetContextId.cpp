#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetContextId(CUcontext context, uint32_t *contextId)
{
	CUptiResult retval = cuptiGetContextId(context, contextId);
	return retval;
}