#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const cuComplex *alpha, const cuComplex *A, int lda, const cuComplex *cscValB, const int *cscColPtrB, const int *cscRowIndB, const cuComplex *beta, cuComplex *C, int ldc)
{
	cusparseStatus_t retval = cusparseCgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
	return retval;
}