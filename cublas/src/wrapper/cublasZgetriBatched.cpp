#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZgetriBatched(cublasHandle_t handle, int n, const cuDoubleComplex * const A[], int lda, const int *P, cuDoubleComplex * const C[], int ldc, int *info, int batchSize)
{
	cublasStatus_t retval = cublasZgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
	return retval;
}