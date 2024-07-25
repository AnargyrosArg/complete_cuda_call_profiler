#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDdot_v2(cublasHandle_t handle, int n, const double *x, int incx, const double *y, int incy, double *result)
{
	cublasStatus_t retval = cublasDdot_v2(handle, n, x, incx, y, incy, result);
	return retval;
}