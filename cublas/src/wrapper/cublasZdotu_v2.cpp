#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZdotu_v2(cublasHandle_t handle, int n, const cuDoubleComplex *x, int incx, const cuDoubleComplex *y, int incy, cuDoubleComplex *result)
{
	cublasStatus_t retval = cublasZdotu_v2(handle, n, x, incx, y, incy, result);
	return retval;
}