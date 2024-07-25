#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSspr2_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *alpha, const float *x, int incx, const float *y, int incy, float *AP)
{
	cublasStatus_t retval = cublasSspr2_v2(handle, uplo, n, alpha, x, incx, y, incy, AP);
	return retval;
}