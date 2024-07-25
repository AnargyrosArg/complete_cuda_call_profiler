#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityGetNumDroppedRecords(CUcontext context, uint32_t streamId, size_t *dropped)
{
	CUptiResult retval = cuptiActivityGetNumDroppedRecords(context, streamId, dropped);
	return retval;
}