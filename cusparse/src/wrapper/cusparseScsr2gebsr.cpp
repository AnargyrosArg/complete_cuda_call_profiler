#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseScsr2gebsr(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cusparseMatDescr_t descrC, float *bsrSortedValC, int *bsrSortedRowPtrC, int *bsrSortedColIndC, int rowBlockDim, int colBlockDim, void *pBuffer)
{
	cusparseStatus_t retval = cusparseScsr2gebsr(handle, dirA, m, n, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, descrC, bsrSortedValC, bsrSortedRowPtrC, bsrSortedColIndC, rowBlockDim, colBlockDim, pBuffer);
	return retval;
}