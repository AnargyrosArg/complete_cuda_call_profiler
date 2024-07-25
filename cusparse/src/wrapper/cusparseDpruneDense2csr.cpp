#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDpruneDense2csr(cusparseHandle_t handle, int m, int n, const double *A, int lda, const double *threshold, const cusparseMatDescr_t descrC, double *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDpruneDense2csr(handle, m, n, A, lda, threshold, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBuffer);
	return retval;
}