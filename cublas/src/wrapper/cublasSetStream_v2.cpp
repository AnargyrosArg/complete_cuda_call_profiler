#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetStream_v2(cublasHandle_t handle, cudaStream_t streamId)
{
	cublasStatus_t retval = cublasSetStream_v2(handle, streamId);
	return retval;
}