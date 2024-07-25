#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCherk_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, int n, int k, const float *alpha, const cuComplex *A, int lda, const float *beta, cuComplex *C, int ldc)
{
	cublasStatus_t retval = cublasCherk_v2(handle, uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
	return retval;
}