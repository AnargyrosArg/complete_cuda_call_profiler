#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSdot_v2(cublasHandle_t handle, int n, const float *x, int incx, const float *y, int incy, float *result)
{
	cublasStatus_t retval = cublasSdot_v2(handle, n, x, incx, y, incy, result);
	return retval;
}