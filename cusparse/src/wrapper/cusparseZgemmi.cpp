#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const cuDoubleComplex *alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *cscValB, const int *cscColPtrB, const int *cscRowIndB, const cuDoubleComplex *beta, cuDoubleComplex *C, int ldc)
{
	cusparseStatus_t retval = cusparseZgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
	return retval;
}