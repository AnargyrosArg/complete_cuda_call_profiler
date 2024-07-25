#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetVectorAsync(int n, int elemSize, const void *devicePtr, int incx, void *hostPtr, int incy, cudaStream_t stream)
{
	cublasStatus_t retval = cublasGetVectorAsync(n, elemSize, devicePtr, incx, hostPtr, incy, stream);
	return retval;
}