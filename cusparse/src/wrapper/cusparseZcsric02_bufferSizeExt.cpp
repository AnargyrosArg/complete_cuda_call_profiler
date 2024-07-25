#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZcsric02_bufferSizeExt(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, cuDoubleComplex *csrSortedVal, const int *csrSortedRowPtr, const int *csrSortedColInd, csric02Info_t info, size_t *pBufferSize)
{
	cusparseStatus_t retval = cusparseZcsric02_bufferSizeExt(handle, m, nnz, descrA, csrSortedVal, csrSortedRowPtr, csrSortedColInd, info, pBufferSize);
	return retval;
}