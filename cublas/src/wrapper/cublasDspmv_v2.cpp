#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDspmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *alpha, const double *AP, const double *x, int incx, const double *beta, double *y, int incy)
{
	cublasStatus_t retval = cublasDspmv_v2(handle, uplo, n, alpha, AP, x, incx, beta, y, incy);
	return retval;
}