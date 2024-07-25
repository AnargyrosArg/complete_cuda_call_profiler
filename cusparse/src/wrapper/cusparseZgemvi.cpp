#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const cuDoubleComplex *alpha, const cuDoubleComplex *A, int lda, int nnz, const cuDoubleComplex *xVal, const int *xInd, const cuDoubleComplex *beta, cuDoubleComplex *y, cusparseIndexBase_t idxBase, void *pBuffer)
{
	cusparseStatus_t retval = cusparseZgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
	return retval;
}