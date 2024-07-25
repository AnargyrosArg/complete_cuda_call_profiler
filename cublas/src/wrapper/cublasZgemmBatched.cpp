#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZgemmBatched(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const cuDoubleComplex *alpha, const cuDoubleComplex * const Aarray[], int lda, const cuDoubleComplex * const Barray[], int ldb, const cuDoubleComplex *beta, cuDoubleComplex * const Carray[], int ldc, int batchCount)
{
	cublasStatus_t retval = cublasZgemmBatched(handle, transa, transb, m, n, k, alpha, Aarray, lda, Barray, ldb, beta, Carray, ldc, batchCount);
	return retval;
}