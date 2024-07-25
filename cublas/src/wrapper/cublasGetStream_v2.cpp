#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetStream_v2(cublasHandle_t handle, cudaStream_t *streamId)
{
	cublasStatus_t retval = cublasGetStream_v2(handle, streamId);
	return retval;
}