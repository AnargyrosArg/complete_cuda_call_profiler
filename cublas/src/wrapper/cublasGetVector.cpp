#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetVector(int n, int elemSize, const void *x, int incx, void *y, int incy)
{
	cublasStatus_t retval = cublasGetVector(n, elemSize, x, incx, y, incy);
	return retval;
}