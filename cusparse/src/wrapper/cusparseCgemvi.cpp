#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const cuComplex *alpha, const cuComplex *A, int lda, int nnz, const cuComplex *xVal, const int *xInd, const cuComplex *beta, cuComplex *y, cusparseIndexBase_t idxBase, void *pBuffer)
{
	cusparseStatus_t retval = cusparseCgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
	return retval;
}