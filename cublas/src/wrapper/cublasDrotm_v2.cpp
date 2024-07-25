#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDrotm_v2(cublasHandle_t handle, int n, double *x, int incx, double *y, int incy, const double *param)
{
	cublasStatus_t retval = cublasDrotm_v2(handle, n, x, incx, y, incy, param);
	return retval;
}