#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDgeqrfBatched(cublasHandle_t handle, int m, int n, double * const Aarray[], int lda, double * const TauArray[], int *info, int batchSize)
{
	cublasStatus_t retval = cublasDgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
	return retval;
}