#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZmatinvBatched(cublasHandle_t handle, int n, const cuDoubleComplex * const A[], int lda, cuDoubleComplex * const Ainv[], int lda_inv, int *info, int batchSize)
{
	cublasStatus_t retval = cublasZmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
	return retval;
}