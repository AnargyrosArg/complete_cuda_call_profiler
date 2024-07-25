#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDgetrfBatched(cublasHandle_t handle, int n, double * const A[], int lda, int *P, int *info, int batchSize)
{
	cublasStatus_t retval = cublasDgetrfBatched(handle, n, A, lda, P, info, batchSize);
	return retval;
}