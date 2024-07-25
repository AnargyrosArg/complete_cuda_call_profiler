#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZgetrfBatched(cublasHandle_t handle, int n, cuDoubleComplex * const A[], int lda, int *P, int *info, int batchSize)
{
	cublasStatus_t retval = cublasZgetrfBatched(handle, n, A, lda, P, info, batchSize);
	return retval;
}