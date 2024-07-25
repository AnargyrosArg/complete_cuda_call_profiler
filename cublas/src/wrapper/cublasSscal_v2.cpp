#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSscal_v2(cublasHandle_t handle, int n, const float *alpha, float *x, int incx)
{
	cublasStatus_t retval = cublasSscal_v2(handle, n, alpha, x, incx);
	return retval;
}