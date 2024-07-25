#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZtrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, cuDoubleComplex *AP)
{
	cublasStatus_t retval = cublasZtrttp(handle, uplo, n, A, lda, AP);
	return retval;
}