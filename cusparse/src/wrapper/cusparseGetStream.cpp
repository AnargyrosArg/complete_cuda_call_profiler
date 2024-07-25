#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseGetStream(cusparseHandle_t handle, cudaStream_t *streamId)
{
	cusparseStatus_t retval = cusparseGetStream(handle, streamId);
	return retval;
}