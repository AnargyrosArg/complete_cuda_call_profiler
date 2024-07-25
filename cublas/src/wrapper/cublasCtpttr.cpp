#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCtpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *AP, cuComplex *A, int lda)
{
	cublasStatus_t retval = cublasCtpttr(handle, uplo, n, AP, A, lda);
	return retval;
}