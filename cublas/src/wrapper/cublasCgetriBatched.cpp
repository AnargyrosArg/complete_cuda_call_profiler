#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCgetriBatched(cublasHandle_t handle, int n, const cuComplex * const A[], int lda, const int *P, cuComplex * const C[], int ldc, int *info, int batchSize)
{
	cublasStatus_t retval = cublasCgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
	return retval;
}