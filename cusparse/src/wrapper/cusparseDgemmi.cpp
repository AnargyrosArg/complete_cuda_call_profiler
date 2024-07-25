#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const double *alpha, const double *A, int lda, const double *cscValB, const int *cscColPtrB, const int *cscRowIndB, const double *beta, double *C, int ldc)
{
	cusparseStatus_t retval = cusparseDgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
	return retval;
}