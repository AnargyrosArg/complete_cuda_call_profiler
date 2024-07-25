#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCbsrsv2_bufferSizeExt(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int mb, int nnzb, const cusparseMatDescr_t descrA, cuComplex *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int blockSize, bsrsv2Info_t info, size_t *pBufferSize)
{
	cusparseStatus_t retval = cusparseCbsrsv2_bufferSizeExt(handle, dirA, transA, mb, nnzb, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockSize, info, pBufferSize);
	return retval;
}