#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasStpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *AP, float *A, int lda)
{
	cublasStatus_t retval = cublasStpttr(handle, uplo, n, AP, A, lda);
	return retval;
}