#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSspr_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *alpha, const float *x, int incx, float *AP)
{
	cublasStatus_t retval = cublasSspr_v2(handle, uplo, n, alpha, x, incx, AP);
	return retval;
}