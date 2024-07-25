#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZhpr_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *alpha, const cuDoubleComplex *x, int incx, cuDoubleComplex *AP)
{
	cublasStatus_t retval = cublasZhpr_v2(handle, uplo, n, alpha, x, incx, AP);
	return retval;
}