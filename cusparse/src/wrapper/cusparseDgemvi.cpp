#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const double *alpha, const double *A, int lda, int nnz, const double *xVal, const int *xInd, const double *beta, double *y, cusparseIndexBase_t idxBase, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
	return retval;
}