#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetStreamIdEx(CUcontext context, CUstream stream, uint8_t perThreadStream, uint32_t *streamId)
{
	CUptiResult retval = cuptiGetStreamIdEx(context, stream, perThreadStream, streamId);
	return retval;
}