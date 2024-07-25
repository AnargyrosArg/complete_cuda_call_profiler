#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSspmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *alpha, const float *AP, const float *x, int incx, const float *beta, float *y, int incy)
{
	cublasStatus_t retval = cublasSspmv_v2(handle, uplo, n, alpha, AP, x, incx, beta, y, incy);
	return retval;
}