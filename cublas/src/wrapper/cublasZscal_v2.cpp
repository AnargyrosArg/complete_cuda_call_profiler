#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZscal_v2(cublasHandle_t handle, int n, const cuDoubleComplex *alpha, cuDoubleComplex *x, int incx)
{
	cublasStatus_t retval = cublasZscal_v2(handle, n, alpha, x, incx);
	return retval;
}