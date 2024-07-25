#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSmatinvBatched(cublasHandle_t handle, int n, const float * const A[], int lda, float * const Ainv[], int lda_inv, int *info, int batchSize)
{
	cublasStatus_t retval = cublasSmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
	return retval;
}