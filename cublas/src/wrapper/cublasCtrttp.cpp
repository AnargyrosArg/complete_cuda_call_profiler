#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCtrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *A, int lda, cuComplex *AP)
{
	cublasStatus_t retval = cublasCtrttp(handle, uplo, n, A, lda, AP);
	return retval;
}