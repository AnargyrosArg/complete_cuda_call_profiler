#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpruneDense2csrByPercentage(cusparseHandle_t handle, int m, int n, const float *A, int lda, float percentage, const cusparseMatDescr_t descrC, float *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, pruneInfo_t info, void *pBuffer)
{
	cusparseStatus_t retval = cusparseSpruneDense2csrByPercentage(handle, m, n, A, lda, percentage, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, info, pBuffer);
	return retval;
}