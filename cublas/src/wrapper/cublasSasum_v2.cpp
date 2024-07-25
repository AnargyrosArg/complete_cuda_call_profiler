#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSasum_v2(cublasHandle_t handle, int n, const float *x, int incx, float *result)
{
	cublasStatus_t retval = cublasSasum_v2(handle, n, x, incx, result);
	return retval;
}