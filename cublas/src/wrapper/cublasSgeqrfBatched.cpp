#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSgeqrfBatched(cublasHandle_t handle, int m, int n, float * const Aarray[], int lda, float * const TauArray[], int *info, int batchSize)
{
	cublasStatus_t retval = cublasSgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
	return retval;
}