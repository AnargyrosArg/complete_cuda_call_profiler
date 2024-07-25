#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const float *alpha, const float *A, int lda, const float *cscValB, const int *cscColPtrB, const int *cscRowIndB, const float *beta, float *C, int ldc)
{
	cusparseStatus_t retval = cusparseSgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
	return retval;
}