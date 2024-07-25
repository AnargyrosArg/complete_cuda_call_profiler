#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetKernelStream(cudaStream_t stream)
{
	cublasStatus_t retval = cublasSetKernelStream(stream);
	return retval;
}