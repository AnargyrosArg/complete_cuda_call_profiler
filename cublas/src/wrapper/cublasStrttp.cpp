#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasStrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *A, int lda, float *AP)
{
	cublasStatus_t retval = cublasStrttp(handle, uplo, n, A, lda, AP);
	return retval;
}