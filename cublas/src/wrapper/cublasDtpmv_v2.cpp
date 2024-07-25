#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDtpmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, cublasDiagType_t diag, int n, const double *AP, double *x, int incx)
{
	cublasStatus_t retval = cublasDtpmv_v2(handle, uplo, trans, diag, n, AP, x, incx);
	return retval;
}