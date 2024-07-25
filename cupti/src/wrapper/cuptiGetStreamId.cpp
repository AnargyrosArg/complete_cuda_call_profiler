#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetStreamId(CUcontext context, CUstream stream, uint32_t *streamId)
{
	CUptiResult retval = cuptiGetStreamId(context, stream, streamId);
	return retval;
}