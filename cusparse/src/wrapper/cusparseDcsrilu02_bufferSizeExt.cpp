#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDcsrilu02_bufferSizeExt(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, double *csrSortedVal, const int *csrSortedRowPtr, const int *csrSortedColInd, csrilu02Info_t info, size_t *pBufferSize)
{
	cusparseStatus_t retval = cusparseDcsrilu02_bufferSizeExt(handle, m, nnz, descrA, csrSortedVal, csrSortedRowPtr, csrSortedColInd, info, pBufferSize);
	return retval;
}