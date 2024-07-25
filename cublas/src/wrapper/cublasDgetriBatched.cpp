#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDgetriBatched(cublasHandle_t handle, int n, const double * const A[], int lda, const int *P, double * const C[], int ldc, int *info, int batchSize)
{
	cublasStatus_t retval = cublasDgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
	return retval;
}