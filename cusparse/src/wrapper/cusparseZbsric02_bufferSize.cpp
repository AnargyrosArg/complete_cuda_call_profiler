#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZbsric02_bufferSize(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nnzb, const cusparseMatDescr_t descrA, cuDoubleComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockDim, bsric02Info_t info, int *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseZbsric02_bufferSize(handle, dirA, mb, nnzb, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockDim, info, pBufferSizeInBytes);
	return retval;
}