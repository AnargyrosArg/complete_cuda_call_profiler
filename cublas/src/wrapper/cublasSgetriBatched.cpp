#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSgetriBatched(cublasHandle_t handle, int n, const float * const A[], int lda, const int *P, float * const C[], int ldc, int *info, int batchSize)
{
	cublasStatus_t retval = cublasSgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
	return retval;
}