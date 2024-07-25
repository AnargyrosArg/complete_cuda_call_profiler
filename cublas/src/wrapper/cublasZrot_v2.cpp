#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZrot_v2(cublasHandle_t handle, int n, cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy, const double *c, const cuDoubleComplex *s)
{
	cublasStatus_t retval = cublasZrot_v2(handle, n, x, incx, y, incy, c, s);
	return retval;
}