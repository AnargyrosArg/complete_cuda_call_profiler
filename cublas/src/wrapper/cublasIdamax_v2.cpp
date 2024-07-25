#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasIdamax_v2(cublasHandle_t handle, int n, const double *x, int incx, int *result)
{
	cublasStatus_t retval = cublasIdamax_v2(handle, n, x, incx, result);
	return retval;
}