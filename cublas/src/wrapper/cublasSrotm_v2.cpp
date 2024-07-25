#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSrotm_v2(cublasHandle_t handle, int n, float *x, int incx, float *y, int incy, const float *param)
{
	cublasStatus_t retval = cublasSrotm_v2(handle, n, x, incx, y, incy, param);
	return retval;
}