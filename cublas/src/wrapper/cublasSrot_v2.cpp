#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSrot_v2(cublasHandle_t handle, int n, float *x, int incx, float *y, int incy, const float *c, const float *s)
{
	cublasStatus_t retval = cublasSrot_v2(handle, n, x, incx, y, incy, c, s);
	return retval;
}