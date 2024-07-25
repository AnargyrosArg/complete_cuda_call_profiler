#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSbsrilu02_bufferSize(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nnzb, const cusparseMatDescr_t descrA, float *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockDim, bsrilu02Info_t info, int *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseSbsrilu02_bufferSize(handle, dirA, mb, nnzb, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockDim, info, pBufferSizeInBytes);
	return retval;
}