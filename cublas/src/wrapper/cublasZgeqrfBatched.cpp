#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZgeqrfBatched(cublasHandle_t handle, int m, int n, cuDoubleComplex * const Aarray[], int lda, cuDoubleComplex * const TauArray[], int *info, int batchSize)
{
	cublasStatus_t retval = cublasZgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
	return retval;
}