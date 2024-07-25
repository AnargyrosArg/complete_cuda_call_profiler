#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDbsrilu02_bufferSizeExt(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nnzb, const cusparseMatDescr_t descrA, double *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockSize, bsrilu02Info_t info, size_t *pBufferSize)
{
	cusparseStatus_t retval = cusparseDbsrilu02_bufferSizeExt(handle, dirA, mb, nnzb, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockSize, info, pBufferSize);
	return retval;
}