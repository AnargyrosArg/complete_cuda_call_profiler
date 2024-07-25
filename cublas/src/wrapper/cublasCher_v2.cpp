#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCher_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *alpha, const cuComplex *x, int incx, cuComplex *A, int lda)
{
	cublasStatus_t retval = cublasCher_v2(handle, uplo, n, alpha, x, incx, A, lda);
	return retval;
}