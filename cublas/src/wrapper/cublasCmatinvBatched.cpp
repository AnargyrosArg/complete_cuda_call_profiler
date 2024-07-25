#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCmatinvBatched(cublasHandle_t handle, int n, const cuComplex * const A[], int lda, cuComplex * const Ainv[], int lda_inv, int *info, int batchSize)
{
	cublasStatus_t retval = cublasCmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
	return retval;
}