#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityFlush(CUcontext context, uint32_t streamId, uint32_t flag)
{
	CUptiResult retval = cuptiActivityFlush(context, streamId, flag);
	return retval;
}