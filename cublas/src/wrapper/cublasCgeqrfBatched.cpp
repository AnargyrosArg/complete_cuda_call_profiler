#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCgeqrfBatched(cublasHandle_t handle, int m, int n, cuComplex * const Aarray[], int lda, cuComplex * const TauArray[], int *info, int batchSize)
{
	cublasStatus_t retval = cublasCgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
	return retval;
}