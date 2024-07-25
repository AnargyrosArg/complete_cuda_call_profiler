#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDpruneDense2csrNnzByPercentage(cusparseHandle_t handle, int m, int n, const double *A, int lda, float percentage, const cusparseMatDescr_t descrC, int *csrRowPtrC, int *nnzTotalDevHostPtr, pruneInfo_t info, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDpruneDense2csrNnzByPercentage(handle, m, n, A, lda, percentage, descrC, csrRowPtrC, nnzTotalDevHostPtr, info, pBuffer);
	return retval;
}