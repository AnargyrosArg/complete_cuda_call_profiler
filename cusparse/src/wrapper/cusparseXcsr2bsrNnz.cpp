#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcsr2bsrNnz(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, int blockDim, const cusparseMatDescr_t descrC, int *bsrSortedRowPtrC, int *nnzTotalDevHostPtr)
{
	cusparseStatus_t retval = cusparseXcsr2bsrNnz(handle, dirA, m, n, descrA, csrSortedRowPtrA, csrSortedColIndA, blockDim, descrC, bsrSortedRowPtrC, nnzTotalDevHostPtr);
	return retval;
}