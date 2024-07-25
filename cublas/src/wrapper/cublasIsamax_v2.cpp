#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasIsamax_v2(cublasHandle_t handle, int n, const float *x, int incx, int *result)
{
	cublasStatus_t retval = cublasIsamax_v2(handle, n, x, incx, result);
	return retval;
}