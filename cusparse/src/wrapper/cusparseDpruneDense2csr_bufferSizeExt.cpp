#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDpruneDense2csr_bufferSizeExt(cusparseHandle_t handle, int m, int n, const double *A, int lda, const double *threshold, const cusparseMatDescr_t descrC, const double *csrSortedValC, const int *csrSortedRowPtrC, const int *csrSortedColIndC, size_t *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseDpruneDense2csr_bufferSizeExt(handle, m, n, A, lda, threshold, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBufferSizeInBytes);
	return retval;
}