#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCsrot_v2(cublasHandle_t handle, int n, cuComplex *x, int incx, cuComplex *y, int incy, const float *c, const float *s)
{
	cublasStatus_t retval = cublasCsrot_v2(handle, n, x, incx, y, incy, c, s);
	return retval;
}