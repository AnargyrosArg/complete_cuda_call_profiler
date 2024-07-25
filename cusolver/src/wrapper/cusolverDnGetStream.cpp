#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnGetStream(cusolverDnHandle_t handle, cudaStream_t *streamId)
{
	cusolverStatus_t retval = cusolverDnGetStream(handle, streamId);
	return retval;
}