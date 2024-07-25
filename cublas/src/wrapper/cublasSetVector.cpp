#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetVector(int n, int elemSize, const void *x, int incx, void *devicePtr, int incy)
{
	cublasStatus_t retval = cublasSetVector(n, elemSize, x, incx, devicePtr, incy);
	return retval;
}