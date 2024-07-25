#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDpruneDense2csrNnz(cusparseHandle_t handle, int m, int n, const double *A, int lda, const double *threshold, const cusparseMatDescr_t descrC, int *csrSortedRowPtrC, int *nnzTotalDevHostPtr, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDpruneDense2csrNnz(handle, m, n, A, lda, threshold, descrC, csrSortedRowPtrC, nnzTotalDevHostPtr, pBuffer);
	return retval;
}