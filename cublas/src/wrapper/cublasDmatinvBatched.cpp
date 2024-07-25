#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDmatinvBatched(cublasHandle_t handle, int n, const double * const A[], int lda, double * const Ainv[], int lda_inv, int *info, int batchSize)
{
	cublasStatus_t retval = cublasDmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
	return retval;
}