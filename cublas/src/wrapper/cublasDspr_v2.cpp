#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDspr_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *alpha, const double *x, int incx, double *AP)
{
	cublasStatus_t retval = cublasDspr_v2(handle, uplo, n, alpha, x, incx, AP);
	return retval;
}