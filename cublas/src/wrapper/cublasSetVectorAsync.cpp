#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetVectorAsync(int n, int elemSize, const void *hostPtr, int incx, void *devicePtr, int incy, cudaStream_t stream)
{
	cublasStatus_t retval = cublasSetVectorAsync(n, elemSize, hostPtr, incx, devicePtr, incy, stream);
	return retval;
}