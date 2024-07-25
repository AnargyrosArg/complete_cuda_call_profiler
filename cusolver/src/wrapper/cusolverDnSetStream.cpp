#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSetStream(cusolverDnHandle_t handle, cudaStream_t streamId)
{
	cusolverStatus_t retval = cusolverDnSetStream(handle, streamId);
	return retval;
}