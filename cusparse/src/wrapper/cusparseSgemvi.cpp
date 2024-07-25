#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const float *alpha, const float *A, int lda, int nnz, const float *xVal, const int *xInd, const float *beta, float *y, cusparseIndexBase_t idxBase, void *pBuffer)
{
	cusparseStatus_t retval = cusparseSgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
	return retval;
}